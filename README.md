how to add more tests:<br />
1.<br />
	read the representation of a 2x2 cube in cube.h<br />
2.<br />
	in tests.h, add a function with the type<br /> 
	bool f(struct cube* c)<br />
3.<br /> 
	let f return true if c has a state that is considered "solved" for this test, and false otherwise<br />
4.<br /> 
	in the array bool (*tests[TESTS])(struct cube*)<br />
	add<br />
	f,<br />
5.<br /> 
	in the array char description_tests[TESTS][50]<br />
	add<br /> 
	"a description of the test",<br />
6.<br /> 
	in #define TESTS x<br />
	increase x by 1<br />
