#include "cocos/base/CCConsole.h"
#include "cocos/platform/CCFileUtils.h"

#include "tinyxmlspriterfiledocumentwrapper.h"

#include "tinyxmlspriterfileelementwrapper.h"

namespace cc = cocos2d;

namespace SpriterEngine
{
	std::map<std::string, tinyxml2::XMLDocument*> TinyXmlSpriterFileDocumentWrapper::DocCache = std::map<std::string, tinyxml2::XMLDocument*>();

	TinyXmlSpriterFileDocumentWrapper::TinyXmlSpriterFileDocumentWrapper()
	{
		doc = nullptr;
	}

	void TinyXmlSpriterFileDocumentWrapper::loadFile(std::string fileName)
	{
		if (TinyXmlSpriterFileDocumentWrapper::DocCache.find(fileName) != TinyXmlSpriterFileDocumentWrapper::DocCache.end())
		{
			doc = TinyXmlSpriterFileDocumentWrapper::DocCache[fileName];
			return;
		}

		cc::Data data = cc::FileUtils::getInstance()->getDataFromFile(fileName);

		if (!data.isNull())
		{
			tinyxml2::XMLDocument* newDoc = new tinyxml2::XMLDocument();

			int rc = newDoc->Parse((const char*)data.getBytes(), data.getSize());
			
			if (rc == 0)
			{
				TinyXmlSpriterFileDocumentWrapper::DocCache[fileName] = newDoc;
				doc = newDoc;
			}
			else
			{
				CCLOG("TinyXML failed to Parse: %s,%d\n",fileName.c_str(),rc);
			}
		}
		else
		{
			CCLOG("TinyXMLSpriterFileDocumentWrapper failed to read data from file: %s", fileName.c_str());
		}
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement()
	{
		return new TinyXmlSpriterFileElementWrapper(doc == nullptr ? nullptr : doc->FirstChildElement());
	}

	SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		return new TinyXmlSpriterFileElementWrapper(doc == nullptr ? nullptr : doc->FirstChildElement(elementName.c_str()));
	}

}