
$$FIRST(\mathrm{datalogProgram}) = \{\mathrm{SCHEMES, FACTS, RULES, QUERIES}\}$$
$$FIRST(\mathrm{schemeList}) = \{ID, \lambda\}$$
$$FIRST(\mathrm{factList}) = \{\mathrm{ID, \lambda}\}$$
$$FIRST(\mathrm{ruleList}) = \{\mathrm{ID, \lambda}\}$$

|              |,|.|?|(|)|:|:-|*|+|Schemes|Facts|Rules|Queries|ID|String|$\lambda$|
|-             |-|-|-|-|-|-|- |-|-|-      |-    |-    |-      |- |-|-
|datalogProgram| | | | | | |  | | |(SCHEMES COLON scheme, schemeList)|(FACTS COLON factList)|(RULES COLON ruleList)|(QUERIES COLON query, queryList)
|schemeList    | | | | | | |  | | | | | | |(scheme schemeList)||(lambda)
|factList||||||||||||||(fact factList)||(lambda)
|ruleList||||||||||||||(rule ruleList)||(lambda)
|queryList||||||||||||||(predicate Q_MARK)||(lambda)
|scheme   ||||||||||||||(ID LEFT_PAREN ID idList RIGHT_PAREN)
|fact     ||||||||||||||(ID LEFT_PAREN STRING stringList RIGHT_PAREN)
|rule     ||||||||||||||(headPredicate COLON_DASH predicate predicateList PERIOD)
|query    ||||||||||||||(predicate, Q_MARK)
|headPredicate||||||||||||||(ID LEFT_PAREN ID idList RIGHT_PAREN)
|predicate||||||||||||||(ID LEFT_PAREN parameter paramterList RIGHT_PAREN)
|predicateList|(COMMA predicate predicateList)|||||||||||||||(lambda)
|parameterList|(COMMA parameter parameterList)|||||||||||||||(lambda)
|stringList|(COMMA STRING stringList)|||||||||||||||(lambda)
|idList|(COMMA ID idList)|||||||||||||||(lambda)
|parameter||||(expression)||||||||||(ID)|(STRING)
|expression||||(LEFT_PAREN parameter operator parameter RIGHT_PAREN)
|operator|||||||(MULTIPLY)(ADD)