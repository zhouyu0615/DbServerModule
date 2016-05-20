#include "stdafx.h"
#include "XmlParser.h"


CXmlParser::CXmlParser()
{
	Init();
}


CXmlParser::~CXmlParser()
{
}


void CXmlParser::SetFilePathName(const CString& fileName)
{
	m_fileName = fileName;
}

void CXmlParser::Init()
{
	m_OperTypeIndexMap["Insert"] = emOperType::Insert;
	m_OperTypeIndexMap["Delete"] = emOperType::Delete;
	m_OperTypeIndexMap["Update"] = emOperType::Update;

	m_tbNameIndexMap["tbUser"] = emTbName::tbUser;
	m_tbNameIndexMap["tbProcessPara"] = emTbName::tbProcessPara;

}

void CXmlParser::ParserFile()
{
	TiXmlDocument xmlfile;
	std::string str = MyCStringToStr(m_fileName);
	bool load = xmlfile.LoadFile(str);

	if (!load)
	{
		LOG2("Load file failed:",str);
		return;
	}

	TiXmlElement* root = xmlfile.RootElement();

	TiXmlNode* pNode=root->FirstChild("OperNode");
	std::string OperType = pNode->ToElement()->GetText();




	switch (m_OperTypeIndexMap[OperType])
	{
	case emOperType::Insert:
		 

		break;
	case  emOperType::Delete:

		break;
	case  emOperType::Update:

		break;;
	default:
		break;
	}
};


void CXmlParser::InsertHandler(TiXmlElement* pNode)
{
	TiXmlElement* pChild = pNode->FirstChildElement("tbName");
	std::string tbName = pChild->ToElement()->GetText();

	switch (m_tbNameIndexMap[tbName])
	{
	case emTbName::tbUser:

		break;
	case emTbName::tbProcessPara:

		break;
	default:
		break;
	}

	return;
};
void CXmlParser::DeleteHandler(TiXmlElement* pNode)
{
	TiXmlElement* pChild = pNode->FirstChildElement("tbName");
	std::string tbName = pChild->ToElement()->GetText();

	return;
};
void CXmlParser::UpdateHandler(TiXmlElement* pNode)
{
	TiXmlElement* pChild = pNode->FirstChildElement("tbName");
	std::string tbName = pChild->ToElement()->GetText();


	return;
};
