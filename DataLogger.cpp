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
        parseTerminal(tokens, TokenType::ID);
        parseTerminal(tokens, TokenType::LEFT_PAREN);
        parseTerminal(tokens, TokenType::ID);
        parseIdList(tokens);
        parseTerminal(tokens, TokenType::RIGHT_PAREN);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseFact(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseTerminal(tokens, TokenType::ID);
        parseTerminal(tokens, TokenType::LEFT_PAREN);
        parseTerminal(tokens, TokenType::STRING);
        parseStringList(tokens);
        parseTerminal(tokens, TokenType::RIGHT_PAREN);
        parseTerminal(tokens, TokenType::PERIOD);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parseRule(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseHeadPredicate(tokens);
        parseTerminal(tokens, TokenType::COLON_DASH);
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

void DataLogger::parseHeadPredicate(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseTerminal(tokens, TokenType::ID);
        parseTerminal(tokens, TokenType::LEFT_PAREN);
        parseTerminal(tokens, TokenType::ID);
        parseIdList(tokens);
        parseTerminal(tokens, TokenType::RIGHT_PAREN);
    }
    else
    {
        throw *tokens;
    }
}

void DataLogger::parsePredicate(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::ID)
    {
        parseTerminal(tokens, TokenType::ID);
        parseTerminal(tokens, TokenType::LEFT_PAREN);
        parseParameter(tokens);
        parseParameterList(tokens);
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

void DataLogger::parseStringList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::COMMA)
    {
        parseTerminal(tokens, TokenType::COMMA);
        parseTerminal(tokens, TokenType::STRING);
        parseStringList(tokens);
    }
}

void DataLogger::parseIdList(std::vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == TokenType::COMMA)
    {
        parseTerminal(tokens, TokenType::COMMA);
        parseTerminal(tokens, TokenType::ID);
        parseIdList(tokens);
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