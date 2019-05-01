# prosedure_test
Memory Malloc Test
-----
|Block Size/Bytes|2|4|8|16|32|64|128|256|512|1024|2048|4096|
|:-|:---:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|-:|
|derect delete after new|308191|275733|206753|203518|203371|204440|301436|318038|324112|315913|307910|298441|
|together delete and new|411967|246037|296358|236625|399467|477640|844479|1640225|2731463|4993028|9375494|17621245|

SIMD test
-------
|Function|ADD|MUL|SUB|DIV|
|:-|:---:|-:|-:|-:|
|simple|6720|6324|147566|137576|
|simd(avx)|1602|1059|1059|1525|

Schema test
----
    // Array
    "{\"type\": \"array\", \"items\": \"long\"}",
    "{\"type\": \"array\",\"items\": {\"type\": \"enum\", "
        "\"name\": \"Test\", \"symbols\": [\"A\", \"B\"]}}"
        
    // Record
    "{\"type\": \"record\",\"name\": \"Test\",\"fields\": "
        "[{\"name\": \"f\",\"type\": \"long\"}]}",
    "{\"type\": \"record\",\"name\": \"Test\",\"fields\": "
        "[{\"name\": \"f1\",\"type\": \"long\"},"
        "{\"name\": \"f2\", \"type\": \"int\"}]}",
    "{\"type\": \"error\",\"name\": \"Test\",\"fields\": "
        "[{\"name\": \"f1\",\"type\": \"long\"},"
        "{\"name\": \"f2\", \"type\": \"int\"}]}",
        
    // Primitive types 
    "{ \"type\": \"null\" }",
    "{ \"type\": \"boolean\" }",
    "{ \"type\": \"int\" }",
    "{ \"type\": \"long\" }",
    "{ \"type\": \"float\" }",
    "{ \"type\": \"double\" }",
    "{ \"type\": \"bytes\" }",
    "{ \"type\": \"string\" }",
