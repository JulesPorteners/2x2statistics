how to add more tests:<br />
1.<br />
*Tabspace* read the representation of a 2x2 cube in cube.h<br />
2.<br />
*Tabspace* in tests.h, add a function with the type<br /> 
*Tabspace* bool f(struct cube* c)<br />
3.<br /> 
*Tabspace* let f return true if c has a state that is considered "solved" for this test, and false otherwise<br />
4.<br /> 
*Tabspace* in the array bool (*tests[TESTS])(struct cube*)<br />
*Tabspace* add<br />
*Tabspace* f,<br />
5.<br /> 
*Tabspace* in the array char description_tests[TESTS][50]<br />
*Tabspace* add<br /> 
*Tabspace* "a description of the test",<br />
6.<br /> 
*Tabspace* in #define TESTS x<br />
*Tabspace* increase x by 1<br />
