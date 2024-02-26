#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include "XMLTokenizer.H"

class Builder;

class Director
{
private:
	enum State
	{
		BEFORE_PROLOG	= 1,
		AFTER_PROLOG,
		PARSING_ELEMENT,
		IN_NONNULL_ELEMENT,
		END
	};
public:
	XMLTokenizer tokenizer;
	Builder* builder;
	Director(const std::string & filename, Builder * builder);
	void continueParsing();
};

#endif // DIRECTOR_H
