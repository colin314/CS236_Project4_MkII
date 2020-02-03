#include "DataLogger.h"

string DataLogger::parse(vector<Token> * const & inputTokens) {
    try
    {
        vector<Token>::iterator it = inputTokens->begin();
        parseDatalogProgram(it);
    }
    catch(const Token& t)
    {
        std::cerr << "Failed!" << std::endl << t.toString() << std::endl;
    }
    
    cout << "Success!" << endl;

    return "";

    //Schemes

    //Facts

    //Rules

    //Queries

    //Domain

    return "Not Implemented";
}

void DataLogger::checkTerminal(vector<Token>::iterator& tokens, TokenType ttype) {
    if (tokens->getTokenType() != ttype) {
        throw* tokens;
    }
    
}

void DataLogger::parseTerminal(vector<Token>::iterator& tokens, TokenType terminalType){
    if (tokens->getTokenType() != terminalType)
    {
        throw *tokens;
    }
    
    ++tokens;
}

void DataLogger::parseDatalogProgram(vector<Token>::iterator& tokens){
    if (tokens->getTokenType() == SCHEMES){
        parseTerminal(tokens, SCHEMES);
        parseTerminal(tokens, COLON);
        parseScheme(tokens);
        parseSchemeList(tokens);
        parseTerminal(tokens, FACTS);
        parseTerminal(tokens, COLON);
        parseFactList(tokens);
        parseTerminal(tokens, RULES);
        parseTerminal(tokens, COLON);
        parseRuleList(tokens);
        parseTerminal(tokens, QUERIES);
        parseTerminal(tokens, COLON);
        parseQuery(tokens);
        parseQueryList(tokens);
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseSchemeList(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        parseScheme(tokens);
        parseSchemeList(tokens);
    }
}

//DONE
void DataLogger::parseFactList(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        parseFact(tokens);
        parseFactList(tokens);
    }
}

//DONE
void DataLogger::parseRuleList(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        parseRule(tokens);
        parseRuleList(tokens);
    }
}

//DONE
void DataLogger::parseQueryList(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        parseQuery(tokens);
        parseQueryList(tokens);
    }
}

//DONE
void DataLogger::parseScheme(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        Scheme* newScheme = new Scheme(*tokens);
        schemes.push_back(newScheme);
        ++tokens;
        parseTerminal(tokens, LEFT_PAREN);
        checkTerminal(tokens, ID);
        newScheme->getIdVector()->push_back(new Token(*tokens));
        ++tokens;
        parseIdList(tokens, newScheme->getIdVector());
        parseTerminal(tokens, RIGHT_PAREN);
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseFact(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        Fact* newFact = new Fact(*tokens);
        facts.push_back(newFact);
        ++tokens;

        parseTerminal(tokens, LEFT_PAREN);
        checkTerminal(tokens, STRING);
        newFact->addString(tokens->getTokenStr());
        ++tokens;
        parseStringList(tokens, newFact->getFactStringList());
        parseTerminal(tokens, RIGHT_PAREN);
        parseTerminal(tokens, PERIOD);
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseRule(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        Rule* newRule = new Rule();
        rules.push_back(newRule);
        parseHeadPredicate(tokens, newRule);
        parseTerminal(tokens, COLON_DASH);
        parsePredicate(tokens, newRule->getPredicateList());
        parsePredicateList(tokens, newRule->getPredicateList());
        parseTerminal(tokens, PERIOD);
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseQuery(vector<Token>::iterator& tokens) {
    if (tokens->getTokenType() == ID)
    {
        parsePredicate(tokens, &queries);
        parseTerminal(tokens, Q_MARK);
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseHeadPredicate(vector<Token>::iterator& tokens, Rule* rule) {
    if (tokens->getTokenType() == ID)
    {
        HeadPredicate*  newHPred = new HeadPredicate(*tokens);
        rule->setHeadPred(newHPred);
        ++tokens;
        parseTerminal(tokens, LEFT_PAREN);
        checkTerminal(tokens, ID);
        newHPred->getIdList()->push_back(new Token(*tokens));
        ++tokens;
        parseIdList(tokens, newHPred->getIdList());
        parseTerminal(tokens, RIGHT_PAREN);
    }
    else { throw *tokens; }
}

//DONE
void DataLogger::parsePredicate(vector<Token>::iterator& tokens, vector<Predicate*>* predList) {
    if (tokens->getTokenType() == ID)
    {
        Predicate* newPred = new Predicate(*tokens);
        predList->push_back(newPred);
        ++tokens;
        parseTerminal(tokens, LEFT_PAREN);
        parseParameter(tokens, newPred->getParameters());
        parseParameterList(tokens, newPred->getParameters());
        parseTerminal(tokens, RIGHT_PAREN);
    }
    else { throw *tokens; }
}

//DONE
void DataLogger::parsePredicateList(vector<Token>::iterator& tokens, vector<Predicate*>* predList) {
    if (tokens->getTokenType() == COMMA)
    {
        parseTerminal(tokens, COMMA);
        parsePredicate(tokens, predList);
        parsePredicateList(tokens, predList);
    }
}

//DONE
void DataLogger::parseParameterList(vector<Token>::iterator& tokens, vector<Parameter*>* paramList) {
    if (tokens->getTokenType() == COMMA)
    {
        parseTerminal(tokens, COMMA);
        parseParameter(tokens, paramList);
        parseParameterList(tokens, paramList);
    }
}

//DONE
void DataLogger::parseStringList(vector<Token>::iterator& tokens, vector<std::string>* stringList) {
    if (tokens->getTokenType() == COMMA)
    {
        ++tokens;
        checkTerminal(tokens, COMMA);
        stringList->push_back(tokens->getTokenStr());
        ++tokens;
        parseStringList(tokens, stringList);
    }
}

//DONE
void DataLogger::parseIdList(vector<Token>::iterator& tokens, vector<Token*>* idList) {
    if (tokens->getTokenType() == COMMA)
    {
        ++tokens;
        checkTerminal(tokens, ID);
        idList->push_back(new Token(*tokens));
        parseIdList(tokens, idList);
    }
}

//DONE
void DataLogger::parseParameter(vector<Token>::iterator& tokens, vector<Parameter*>* paramList) {
    if (tokens->getTokenType() == LEFT_PAREN)
    {
        parseExpression(tokens, paramList);
    }
    else if (tokens->getTokenType() == ID) 
    {
        IdParam* newIdParam = new IdParam();
        paramList->push_back(newIdParam);
        newIdParam->setId(*tokens);
        ++tokens;
    }
    else if (tokens->getTokenType() == STRING)
    {
        StringParam* newStrParam = new StringParam();
        paramList->push_back(newStrParam);
        newStrParam->setString(*tokens);
        ++tokens;
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseExpression(vector<Token>::iterator& tokens, vector<Parameter*>* paramList) {
    if (tokens->getTokenType() == LEFT_PAREN)
    {
        ExpParam* newExpr = new ExpParam();
        paramList->push_back(newExpr);

        parseTerminal(tokens, LEFT_PAREN);
        parseParameter(tokens, newExpr->getExpression()->getParams());
        parseOperator(tokens, newExpr->getExpression()->getOperatorToken());
        parseParameter(tokens, newExpr->getExpression()->getParams());
        parseTerminal(tokens, RIGHT_PAREN);
    }
    else
    {
        throw *tokens;
    }
}

//DONE
void DataLogger::parseOperator(vector<Token>::iterator& tokens, Token* opTkn) {
    if (opTkn != nullptr) {
        delete opTkn;
        opTkn = nullptr;
    }
    if (tokens->getTokenType() == ADD)
    {
        opTkn = new Token(*tokens);
        ++tokens;
    }
    else if (tokens->getTokenType() == MULTIPLY)
    {
        opTkn = new Token(*tokens);
        ++tokens;
    }
    else
    {
        throw *tokens;
    }
}