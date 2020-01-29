#include "DataLogger.h"

string DataLogger::parse(std::vector<Token> * const & inputTokens) {
    try
    {
        std::vector<Token>::iterator it = inputTokens->begin();
        parseDatalogProgram(it);
    }
    catch(const Token& t)
    {
        std::cerr << "Failed!" << std::endl << t.toString() << std::endl;
    }
    
    cout << "Success!" << endl;

    while (outputQueue->size() > 0) {
        cout << outputQueue->front().getTokenStr() << endl;
        outputQueue->pop();
    }

    //Schemes

    //Facts

    //Rules

    //Queries

    //Domain

    return "Not Implemented";
}

void DataLogger::parseTerminal(std::vector<Token>::iterator& tokens, TokenType terminalType){
    if (tokens->getTokenType() != terminalType)
    {
        throw *tokens;
    }
    
    outputQueue->push(*tokens);
    ++tokens;
}

void DataLogger::parseDatalogProgram(std::vector<Token>::iterator& tokens){
    if (tokens->getTokenType() == TokenType::SCHEMES){
        parseTerminal(tokens, TokenType::SCHEMES);
        parseTerminal(tokens, TokenType::COLON);
        parseScheme(tokens);
        parseSchemeList(tokens);
        parseTerminal(tokens, TokenType::FACTS);
        parseTerminal(tokens, TokenType::COLON);
        parseFactList(tokens);
        parseTerminal(tokens, TokenType::RULES);
        parseTerminal(tokens, TokenType::COLON);
        parseRuleList(tokens);
        parseTerminal(tokens, TokenType::QUERIES);
        parseTerminal(tokens, TokenType::COLON);
        parseQuery(tokens);
        parseQueryList(tokens);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseSchemeList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseScheme(tokens);
        parseSchemeList(tokens);
    }
}

void DataLogger::parseFactList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseFact(tokens);
        parseFactList(tokens);
    }
    
}

void DataLogger::parseRuleList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseRule(tokens);
        parseRuleList(tokens);
    }
    
}

void DataLogger::parseQueryList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parsePredicate(tokens);
        parseTerminal(tokens, TokenType::Q_MARK);
    }
    
}

void DataLogger::parseScheme(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        Scheme* newScheme = new Scheme(*tokens);
        ++tokens;
        if (tokens->getTokenType() != TokenType::LEFT_PAREN) { throw *tokens; }
        ++tokens;
        if (tokens->getTokenType() != TokenType::ID) { throw *tokens; }
        newScheme->getIdVector()->push_back(*tokens);
        ++tokens;
        parseIdList(tokens, newScheme->getIdVector());
        if (tokens ->getTokenType() != TokenType::RIGHT_PAREN) { throw *tokens; }
        ++tokens;
        schemes.push_back(newScheme);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseFact(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        Fact* newFact = new Fact(*tokens);
        ++tokens;
        if (tokens->getTokenType() != TokenType::LEFT_PAREN) { throw *tokens; }
        ++tokens;
        if (tokens->getTokenType() != TokenType::STRING) {throw *tokens; }
        newFact->addString(tokens->getTokenStr());
        ++tokens;
        parseStringList(tokens, newFact->getFactStringList());
        if (tokens ->getTokenType() != TokenType::RIGHT_PAREN) { throw *tokens; }
        ++tokens;
        if (tokens->getTokenType() != TokenType::PERIOD) {throw *tokens; }
        ++tokens;
        facts.push_back(newFact);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseRule(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        Rule* newRule = new Rule();
        parseHeadPredicate(tokens, newRule);
        if (tokens->getTokenType() != TokenType::COLON_DASH) { throw *tokens; }
        ++tokens;
        parsePredicate(tokens);
        parsePredicateList(tokens);
        parseTerminal(tokens, TokenType::PERIOD);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseQuery(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parsePredicate(tokens);
        parseTerminal(tokens, TokenType::Q_MARK);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseHeadPredicate(std::vector<Token>::iterator& tokens, Rule* rule) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        HeadPredicate*  newHPred = new HeadPredicate(*tokens);
        ++tokens;
        if (tokens->getTokenType() != TokenType::LEFT_PAREN) { throw *tokens; }
        ++tokens;
        if (tokens->getTokenType() != TokenType::ID) { throw *tokens; }
        ++tokens;
        newHPred->getIdList()->push_back(*tokens);
        parseIdList(tokens, newHPred->getIdList());
        if (tokens->getTokenType() != TokenType::RIGHT_PAREN) { throw *tokens; }
        ++tokens;

    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parsePredicate(std::vector<Token>::iterator& tokens, std::vector<Predicate*>* predList) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        Predicate* newPred = new Predicate(*tokens);
        ++tokens;
        parseTerminal(tokens, TokenType::LEFT_PAREN);
        parseParameter(tokens);
        parseParameterList(tokens);
        if (/* condition */)
        {
            /* code */
        }
        
        parseTerminal(tokens, TokenType::RIGHT_PAREN);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parsePredicateList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::COMMA)
    {
        parseTerminal(tokens, TokenType::COMMA);
        parsePredicate(tokens);
        parsePredicateList(tokens);
    }
}

void DataLogger::parseParameterList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::COMMA)
    {
        parseTerminal(tokens, TokenType::COMMA);
        parseParameter(tokens);
        parseParameterList(tokens);
    }
}

void DataLogger::parseStringList(std::vector<Token>::iterator& tokens, std::vector<std::string>* stringList) {
    if (tokens->getTokenType() == TokenType::COMMA)
    {
        ++tokens;
        if (tokens->getTokenType() != TokenType::STRING) { throw *tokens; }
        stringList->push_back(tokens->getTokenStr());
        ++tokens;
        parseStringList(tokens, stringList);
    }
}

void DataLogger::parseIdList(std::vector<Token>::iterator& tokens, std::vector<Token>* idList) {
    if (tokens->getTokenType() == TokenType::COMMA)
    {
        ++tokens;
        if (tokens->getTokenType() != TokenType::ID) { throw *tokens; }
        idList->push_back(*tokens);
        parseIdList(tokens, idList);
    }
}

void DataLogger::parseParameter(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::LEFT_PAREN)
    {
        parseExpression(tokens);
    }
    else if (tokens->getTokenType() == TokenType::ID) 
    {
        parseTerminal(tokens, TokenType::ID);
    }
    else if (tokens->getTokenType() == TokenType::STRING)
    {
        parseTerminal(tokens, TokenType::STRING);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseExpression(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::LEFT_PAREN)
    {
        parseTerminal(tokens, TokenType::LEFT_PAREN);
        parseParameter(tokens);
        parseOperator(tokens);
        parseParameter(tokens);
        parseTerminal(tokens, TokenType::RIGHT_PAREN);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseOperator(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ADD)
    {
        parseTerminal(tokens, TokenType::ADD);
    }
    else if (tokens->getTokenType() == TokenType::MULTIPLY)
    {
        parseTerminal(tokens, TokenType::MULTIPLY);
    }
    else
    {
        throw *tokens;
    }
}