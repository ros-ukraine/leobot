# Contributing to LeoBot

## Questions and issues
In case if you have any questions please create issue and mark it with label `question`.

If you have found the bug in the code please provide the following information:
* Steps to reproduce
* Actual Behaviour
* Expected Behaviour
Please label appropriate issue with label `bug`.

## Coding Style

Please make sure that your code is following ROS coding style for:
* [Python](http://wiki.ros.org/PyStyleGuide)
* [C++](http://wiki.ros.org/CppStyleGuide)
* [Javascript](http://wiki.ros.org/JavaScriptStyleGuide)

## Pull Requests

* Use one of the [closing issue keywords](https://help.github.com/articles/closing-issues-using-keywords/) in PR description
* Make sure that all Continious Integration servers are green

## New Packages

Whenever you are introducing new package please create PR with basic structure: CMakeLists.txt and package.xml files.
This will allow to decrease size of real code PR.

## Messages, Services and Actions

Please put definitions of all messages, services and actions definitions to `leobot_msgs` package.

## Styleguides

### Branch names

For feature implementation please use the following format `F#No_description`.
Bug fixing branch should be `B#No_description`. 
`#No` is an issue number in GitHub. 

### Git Commit Messages

* All commit messages should shortly describe made by commit
* When only changing documentation, include `[ci skip]` in the commit description

### Documentation Styleguide

* Use [Markdown](https://daringfireball.net/projects/markdown).

## Additional Notes

### Code Update
Sometimes after code update from main branch you can have compilation issue.
This might be due to new dependencies which are needed for new or updated packages.
To get all needed packages do the following.

```bash
roscd
cd ../src
depkinetic
``` 
After that recompile code again.
