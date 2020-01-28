#pragma once



enum TokenType {
    COMMA=0,
    PERIOD=1,
    Q_MARK=2,
    LEFT_PAREN=3,
    RIGHT_PAREN=4,
    COLON=5,
    COLON_DASH=6,
    MULTIPLY=7,
    ADD=8,
    SCHEMES=9,
    FACTS=10,
    RULES=11,
    QUERIES=12,
    ID=13,
    STRING=14,
    COMMENT=15,
    UNDEFINED=16,
    _EOF=17,
    EXPRESSION = 18
};

inline std::string tokenTypeToString(const TokenType& ttype) {
    switch (ttype)
    {
    case COMMA:       return "COMMA";      
    case PERIOD:      return "PERIOD";     
    case Q_MARK:      return "Q_MARK";     
    case LEFT_PAREN:  return "LEFT_PAREN"; 
    case RIGHT_PAREN: return "RIGHT_PAREN";
    case COLON:       return "COLON";      
    case COLON_DASH:  return "COLON_DASH"; 
    case MULTIPLY:    return "MULTIPLY";   
    case ADD:         return "ADD";        
    case SCHEMES:     return "SCHEMES";    
    case FACTS:       return "FACTS";       
    case RULES:       return "RULES";      
    case QUERIES:     return "QUERIES";    
    case ID:          return "ID";         
    case STRING:      return "STRING";     
    case COMMENT:     return "COMMENT";    
    case UNDEFINED:   return "UNDEFINED";  
    case _EOF:        return "EOF";        
    case EXPRESSION:  return "EXPRESSION";
    default:
        return "";
    }
}

inline std::ostream& operator<<(std::ostream& os, const TokenType ttype) {
    os << tokenTypeToString(ttype);
    return os;
}