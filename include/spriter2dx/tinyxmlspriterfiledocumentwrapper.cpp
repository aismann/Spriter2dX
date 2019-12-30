#include "cocos/base/CCConsole.h"
#include "cocos/platform/CCFileUtils.h"

#include "tinyxmlspriterfiledocumentwrapper.h"

#include "tinyxmlspriterfileelementwrapper.h"

namespace cc = cocos2d;

namespace SpriterEngine
{
	TinyXmlSpriterFileDocumentWrapper::TinyXmlSpriterFileDocumentWrapper()
	{
	}

	void TinyXmlSpriterFileDocumentWrapper::loadFile(std::string fileName)
	{
		cc::Data data = cc::FileUtils::getInstance()->getDataFromFile(fileName);
		if (!data.isNull())
		{
			int rc = doc.Parse((const char*)data.getBytes(), data.getSize());
			if (rc != 0) {
				CCLOG("TinyXML failed to Parse: %s,%d\n",fileName.c_str(),rc);
			}
		} else {
			CCLOG("TinyXMLSpriterFileDocumentWrapper failed to read data from file: %s", fileName.c_str());
		}
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement()
	{
		return new TinyXmlSpriterFileElementWrapper(doc.FirstChildElement());
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		return new TinyXmlSpriterFileElementWrapper(doc.FirstChildElement(elementName.c_str()));
	}

}