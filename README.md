how to add more tests:<br />
1.<br />
&nbsp; read the representation of a 2x2 cube in cube.h<br />
2.<br />
&nbsp; in tests.h, add a function with the type<br /> 
&nbsp; bool f(struct cube* c)<br />
3.<br /> 
&nbsp; let f return true if c has a state that is considered "solved" for this test, and false otherwise<br />
4.<br /> 
&nbsp; in the array bool (*tests[TESTS])(struct cube*)<br />
&nbsp; add<br />
&nbsp; f,<br />
5.<br /> 
&nbsp; in the array char description_tests[TESTS][50]<br />
&nbsp; add<br /> 
&nbsp; "a description of the test",<br />
6.<br /> 
&nbsp; in #define TESTS x<br />
&nbsp; increase x by 1<br />
