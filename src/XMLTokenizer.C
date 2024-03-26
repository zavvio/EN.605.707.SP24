#include "XMLTokenizer.H"
#include <algorithm>

const char *	XMLTokenizer::PROLOG_START	= "<\\?";
const char *	XMLTokenizer::PROLOG_IDENTIFIER	= "[[:space:]]*xml";
const char *	XMLTokenizer::ATTRIBUTE_VALUE	= "\"[^\"]*\"";
const char *	XMLTokenizer::PROLOG_END	= "[[:space:]]*\\?>";
const char *	XMLTokenizer::TAG_START		= "[[:space:]]*<";
const char *	XMLTokenizer::ELEMENT		= "[[:space:]]*[[:alpha:]]([[:alnum:]_-]|:)*";
const char *	XMLTokenizer::ATTRIBUTE		= "[[:space:]]+[[:alpha:]]([[:alnum:]_-]|:)*[[:space:]]*=";
const char *	XMLTokenizer::NULL_TAG_END	= "[[:space:]]*/>";
const char *	XMLTokenizer::TAG_CLOSE_START	= "[[:space:]]*</";
const char *	XMLTokenizer::VALUE		= "[^<]*";
const char *	XMLTokenizer::TAG_END		= "[[:space:]]*>";
const char *	XMLTokenizer::SPACE_TO_EOL	= "[[:space:]]*";

XMLTokenizer::XMLToken::XMLToken(const std::string & t, TokenTypes tt) : token(t), token_type(tt) {}


const std::string XMLTokenizer::XMLToken::getCleanToken(void)
{
    std::string cleanToken = token;
    //cleanToken.erase(std::remove(cleanToken.begin(), cleanToken.end(), ' '), cleanToken.end());
    cleanToken.erase(cleanToken.begin(), std::find_if(cleanToken.begin(), cleanToken.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
    //cleanToken.erase(cleanToken.begin(), std::find_if(cleanToken.begin(), cleanToken.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
    cleanToken.erase(std::remove(cleanToken.begin(), cleanToken.end(), '='), cleanToken.end());
    cleanToken.erase(std::remove(cleanToken.begin(), cleanToken.end(), '"'), cleanToken.end());
    return cleanToken;
}

const char *	XMLTokenizer::XMLToken::toString(void)
{
    switch(token_type)
    {
    case NULL_TOKEN:
        return "NULL";
    case PROLOG_START:
        return "PROLOG_START";
    case PROLOG_IDENTIFIER:
        return "PROLOG_IDENTIFIER";
    case ATTRIBUTE_VALUE:
        return "ATTRIBUTE_VALUE";
    case PROLOG_END:
        return "PROLOG_END";
    case TAG_START:
        return "TAG_START";
    case ELEMENT:
        return "ELEMENT";
    case ATTRIBUTE:
        return "ATTRIBUTE";
    case NULL_TAG_END:
        return "NULL_TAG_END";
    case TAG_CLOSE_START:
        return "TAG_CLOSE_START";
    case VALUE:
        return "VALUE";
    case TAG_END:
        return "TAG_END";
    default:
        return "NULL";
    }
}

XMLTokenizer::XMLTokenizer(ChangeManager* changeManager) :
  Subject(changeManager),
  //file(filename.c_str(), std::ios_base::in),
  line_number(0),
  index(0),
  inside_tag(false),
  pending_attribute_value(false),
  tag_found(false),
  prolog_start(PROLOG_START),
  prolog_identifier(PROLOG_IDENTIFIER),
  attribute_value(ATTRIBUTE_VALUE),
  prolog_end(PROLOG_END),
  tag_start(TAG_START),
  element(ELEMENT),
  attribute(ATTRIBUTE),
  null_tag_end(NULL_TAG_END),
  tag_close_start(TAG_CLOSE_START),
  value(VALUE),
  tag_end(TAG_END),
  space_to_eol(SPACE_TO_EOL)
{
}

XMLTokenizer::XMLToken *	XMLTokenizer::getNextToken(void)
{
    if (line.size() == 0)
    {
        std::getline(file, line);
        index	= 0;
        line_number++;

        if (line.size() == 0)
            return new XMLToken(std::string(""), XMLToken::NULL_TOKEN);
    }

    std::smatch	what;

    if (inside_tag)
    {
        if (!tag_found && std::regex_search(line, what, prolog_identifier))
        {
            XMLToken * token = new XMLToken(std::string(what[0].first, what[0].second), XMLToken::PROLOG_IDENTIFIER);
            update_matchers(what[0], what.suffix());
            tag_found	= true;
            return	token;
        }

        if (!tag_found && std::regex_search(line, what, element))
        {
            XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::ELEMENT);
            update_matchers(what[0], what.suffix());
            tag_found	= true;
            return	token;
        }

        if (pending_attribute_value && std::regex_search(line, what, attribute_value))
        {
            XMLToken *	token = new XMLToken(std::string(what[0].first, what[0].second), XMLToken::ATTRIBUTE_VALUE);
            update_matchers(what[0], what.suffix());
            pending_attribute_value	= false;
            return	token;
        }

        if (std::regex_search(line, what, attribute))
        {
            XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::ATTRIBUTE);
            update_matchers(what[0], what.suffix());
            pending_attribute_value	= true;
            return	token;
        }

        if (std::regex_search(line, what, null_tag_end))
        {
            XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::NULL_TAG_END);
            inside_tag		= false;
            pending_attribute_value	= false;
            tag_found		= false;
            update_matchers(what[0], what.suffix());
            return	token;
        }

        if (std::regex_search(line, what, prolog_end))
        {
            XMLToken* token = new XMLToken(std::string(what[0].first, what[0].second), XMLToken::PROLOG_END);
            inside_tag = false;
            pending_attribute_value = false;
            tag_found = false;
            update_matchers(what[0], what.suffix());
            return	token;
        }

        if (std::regex_search(line, what, tag_end))
        {
            XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::TAG_END);
            inside_tag		= false;
            pending_attribute_value	= false;
            tag_found		= false;
            update_matchers(what[0], what.suffix());
            return	token;
        }

    }

    if (std::regex_search(line, what, prolog_start))
    {
        XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::PROLOG_START);
        inside_tag		= true;
        update_matchers(what[0], what.suffix());
        return	token;
    }

    if (std::regex_search(line, what, prolog_end))
    {
        XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::PROLOG_END);
        inside_tag		= false;
        update_matchers(what[0], what.suffix());
        return	token;
    }

    if (std::regex_search(line, what, tag_close_start))
    {
        XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::TAG_CLOSE_START);
        inside_tag		= true;
        update_matchers(what[0], what.suffix());
        return	token;
    }

    if (std::regex_search(line, what, tag_start))
    {
        XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::TAG_START);
        inside_tag		= true;
        update_matchers(what[0], what.suffix());
        return	token;
    }
    if (std::regex_search(line, what, value))
    {
        XMLToken *	token	= new XMLToken(std::string(what[0].first, what[0].second), XMLToken::VALUE);
        update_matchers(what[0], what.suffix());
        return	token;
    }

    if (std::regex_search(line, what, space_to_eol))
    {
        update_matchers(what[0], what.suffix());
        return	getNextToken();
    }

    return new XMLToken(std::string(""), XMLToken::NULL_TOKEN);
}

void		XMLTokenizer::update_matchers(const std::ssub_match & matcher, const std::ssub_match & suffix)
{
    if (matcher.str().size() >= line.size())
    {
        line.clear();
        return;
    }

    line	= suffix.str();
    index	+= matcher.str().size();
}

//DOM* XMLTokenizer::construct(XMLBuilder* builder)
//{
//	builder->BuildDocument();
//	builder->BuildElement("Hello");
//	builder->BuildElement("World");
//	builder->BuildAttribute("Temperature", "25c");
//	builder->BuildAttribute("Foo", "Bar");
//	builder->BuildText("Amazing");
//	return builder->GetDOM();
//}

void XMLTokenizer::rewind()
{
    file.clear();
    file.seekg(0, file.beg);

    line_number = 0;
    index = 0;
    inside_tag = false;
    pending_attribute_value = false;
    tag_found = false;
}

void XMLTokenizer::initialize(const std::string& filename)
{
    file = std::fstream(filename.c_str(), std::ios_base::in);
    _state = filename;
    this->notify();
}

DOM* XMLTokenizer::construct(XMLBuilder* builder)
{
    rewind();
    XMLTokenizer::XMLToken* token = 0;
    std::string tokenString;
    bool skipClosingElement = false;

    do
    {
        delete	token;
        token = getNextToken();

        //printf("\tLine %d:  %s = '%s'\n", getLineNumber(),
        //    token->toString(), token->getToken().size() == 0 ? "" : token->getToken().c_str());

        switch (token->getTokenType())
        {
        case XMLTokenizer::XMLToken::NULL_TAG_END:
            builder->popProbe();
            break;
        case XMLTokenizer::XMLToken::TAG_CLOSE_START:
            skipClosingElement = true;
            builder->popProbe();
            break;
        case XMLTokenizer::XMLToken::PROLOG_START:
            builder->BuildDocument();
            break;
        case XMLTokenizer::XMLToken::ATTRIBUTE:
            tokenString = token->getCleanToken();
            //printf("%s\n", tokenString.c_str());
            break;
        case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
            //tokenString = token->getCleanToken();
            //printf("%s\n", tokenString.c_str());
            builder->BuildAttribute(tokenString, token->getCleanToken());
            break;
        case XMLTokenizer::XMLToken::ELEMENT:
            if (skipClosingElement == true)
            {
                skipClosingElement = false;
                break;
            }
            tokenString = token->getCleanToken();
            //printf("%s\n", tokenString.c_str());
            builder->BuildElement(tokenString);
            break;
        case XMLTokenizer::XMLToken::VALUE:
            tokenString = token->getCleanToken();
            //printf("%s\n", tokenString.c_str());
            builder->BuildText(tokenString);
            break;
        default:
            break;
        }

    } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

    delete	token;

    return builder->GetDOM();
}

std::string XMLTokenizer::getState()
{
	return _state;
};