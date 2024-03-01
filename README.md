# test-duplication-code
I want to create some test cases to check the ability to detect duplication code on C code. This repository worth is store this test cases and document my finds.


## List of Candidate Tools to Test

https://pmd.github.io/pmd/pmd_userdocs_cpd

- Only able to detect repetition of TOKEN when specify TOKEN size. 
- Installed and tested it. Prety simple tool.

https://cppdepend.com/blog/tracking-the-hidden-duplicate-code-in-a-c-code-base/

- It is a paid tool. Should I try it? I think not.
- There is a free trial.

https://github.com/dlidstrom/Duplo

- I like it. It is only able to detect repetition of TOKEN.
- For the tool. TOKEN is defined as a set of consecutive lines with a minimum size per line.
- The output is easy to undertand and usage is easy with docker.
- Prety simple tool.

https://simian.quandarypeak.com/

- It is a paid tool. Should I try it? I think not.
- There is a license for academic research and education use.

https://codeclimate.com/

- It is a paid tool. 
- It is free tool for open source projects. It is fully automate on a website
- Search through github repository.
- Do not check any .c file. Maybe I will try later with change extension to .cpp.

