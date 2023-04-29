#ifndef TINYXMLSPRITERFILEDOCUMENTWRAPPER_H
#define TINYXMLSPRITERFILEDOCUMENTWRAPPER_H

#include "../SpriterPlusPlus/tinyxml2/tinyxml2.h"

#include "../SpriterPlusPlus/spriterengine/override/spriterfiledocumentwrapper.h"

namespace SpriterEngine
{
	class TinyXmlSpriterFileDocumentWrapper : public SpriterFileDocumentWrapper
	{
	public:
		TinyXmlSpriterFileDocumentWrapper();

		void loadFile(std::string fileName) override;

	private:
		SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

		tinyxml2::XMLDocument doc;
	};

}

#endif // TINYXMLSPRITERFILEDOCUMENTWRAPPER_H