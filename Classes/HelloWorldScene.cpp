#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() ) {
        return false;
    }

	bool bRet = m_QRCoder.EncodeData(0, 0, 1, -1, "https://www.baidu.com/");
	if (bRet) {
		int nSize = 5;
		int originalSize = m_QRCoder.m_nSymbleSize + (QR_MARGIN * 2);
		CCDrawNode *pQRNode = CCDrawNode::create();

		CCPoint pt[6];
		ccColor4F color;

		pt[0] = ccp(0, 0);
		pt[1] = ccp((m_QRCoder.m_nSymbleSize + QR_MARGIN * 2)*nSize, (m_QRCoder.m_nSymbleSize + QR_MARGIN * 2)*nSize);
		pt[2] = ccp((m_QRCoder.m_nSymbleSize + QR_MARGIN * 2)*nSize, 0);

		pt[3] = pt[0];
		pt[4] = ccp(0, (m_QRCoder.m_nSymbleSize + QR_MARGIN * 2)*nSize);
		pt[5] = pt[1];
		color = ccc4f(1, 1, 1, 1);
		pQRNode->drawPolygon(pt, 6, color, 0, color);

		for (int i = 0; i < m_QRCoder.m_nSymbleSize; ++i)
		{
			for (int j = 0; j < m_QRCoder.m_nSymbleSize; ++j)
			{
				pt[0] = ccp((i + QR_MARGIN)*nSize, (j + QR_MARGIN)*nSize);
				pt[1] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 1)*nSize);
				pt[2] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 0)*nSize);

				pt[3] = pt[0];
				pt[4] = ccp(((i + QR_MARGIN) + 0)*nSize, ((j + QR_MARGIN) + 1)*nSize);
				pt[5] = pt[1];
				if (m_QRCoder.m_byModuleData[i][j] == 1)
				{
					color = ccc4f(0, 0, 0, 1);
				}
				else
				{
					color = ccc4f(1, 1, 1, 1);
				}
				pQRNode->drawPolygon(pt, 6, color, 0, color);
			}
		}
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		pQRNode->setPosition(ccp((winSize.width - nSize * m_QRCoder.m_nSymbleSize) / 2, winSize.height - (winSize.height - nSize * m_QRCoder.m_nSymbleSize) / 2));
		pQRNode->setScaleY(-1);
		addChild(pQRNode);
	}

    return true;
}
