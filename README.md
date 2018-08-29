# NCTU_Oryx

The competition codebook for team NCTU_Oryx, along with the codebook tester and generator.

## Environment Requirements

* LaTeX along with PDFLaTeX
* python3

## Usage: Codebook Generator

In C/C++ code(and plain text files), the control sequence start with `---codebook` can be used to mark the range of code you want to use. They are conformed into C-style comments:

```cpp
#include <stdio.h>
#DEFINE SOMEOTHERSTUFF
/*---codebook desc
Here can insert raw \LaTeX paragraph/math syntax here, the generator will copy this block of comment verbatim into codebook
*/
//---codebook start
printf("Here would be the code"); 
//---codebook end
int main() {
	printf("Some test code can be placed here, and wiill be ignored by the generator");
}
```

Then in `spec.py` you can specify what snippet to include(in the python Dict `sections`):

```python
graph = {
    'Cut Vertex and BCC':'Graph/CutBCC.cpp'
}

sections = {
    'Graph':graph,
}
```

Finally, use `python3 codebook.py gen [-v]` to generate pdf version of codebook(You may modify template.tex if you want), the `-v` argument will show the output message from pdflatex.

## Usage: Codebook tester

First place your test data in a seperate directory under `tests`. The filename of input data should have `.in` extension, the filename of correct output data should have `.out` extension, and they must have same filename.

Then in the corresponding code to test, you may put(one or more) control sequence in the comment too:
```cpp
//---codebook test=Math/extgcd
```

After that issue `python3 codebook.py test [all]`, you will see the verdict of each specified testsuite. The `all` argument will test all the snnipet in the directory, even when they are not in `spec.py`.
![Codebook Test](/codebook_test.png?raw=true)
