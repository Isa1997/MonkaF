#include <algorithm>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#define SHOW_EXAMPLES

/*
What is SuperFunction?
SuperFunction is function, that takes functions as argument, and creates an function!

.... ......................*%@@@@@@@@@@@@@@@@@&%,*.*,,,,,,,,,,,,,,,,,,,,....................... . .
.                .   ..,@&&@(%%##&&&#/%&#%&%%%&&&&(/((,........,,.,,,...................
.       . . ........,%&&&&&@&&@%#**,**(%&&&/(**#((&@@&*,..,...,..,,.,,,,,,,................
.     .. ..........,&&###(/(((#%%%%%#####(((((#((#&@&&(#/*,,.,.,,,,,,,,,,,,,,,,,,,............
.     ...........,,#%(##((%%&@&&&%%%####%%####(((/(@%(&#&/,,,,,,,,,,,,,,,,,,,,,,,,..,............ .
. . ............../(/(/&@@@@@@&%%%%%%#@&%&@@@@&%/**(&&&#&%(*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..........
. . ............,@@@@@&&@@@@@&&%%%%%#(((&((#%&@@@@@&@@(//&&**,,*,*,,,*,,*,*,,*,**,,,,,,,,,,........
. .........(%@@&@@@&((/&&%(/(///##(//#(/%%&@&(%%%%%&&@&&@%#(*,,,,,*,,,,,,,,,,,,*,*,,,,,,,,,,.,.....
........&@@&@@&%#(((##%&#(*#***#/(#//**,***#/((#%&@%#%%%%&@@@@*,,,,,,**,,**,,,,,,,,,,,,,,,,,,.,....
......@@@&%###*,#@**(#&&%&%#/**(&%/*******\///(((((#&@@&&&@@@@@@,*,*,,,,,,**,,,,,,,,,,,,,,,,.......
...@@@@&%#&@@&%#(*,*((%@@&%(#&%#&(//*\/***\///((#%##(((##%@&&@@@@@@,*,,,*,*,,,,,*,,,,,,,,,,,.......
.@@@@%@@%##(((/,,,,,/%#&&((((((&%(/*\//***\///(((###**((((###&@@@@@@&,,,,,,*,,*,,,,,,,,,,,,,,......
@@@@@&((/(,,,,,,,,*,*&(&%(/////((/********\/////((**,##(((((##%&@@@@@&,*,,,*,,,,,,,,,,,,,,,,,,.....
@@&%#((((%.,,,,%@@@&%*\/%%%//((%(/********\//////*,**(&%%###(###%&@@@@%,,,*,,,,,,,,,,,,,,,,........
&%(((((((#&&&#(///*****\/%%(//#((//***************\\((&/,%###((((##&@@@@@&/*,,*,,,,,,,,,,,,,.,.....
(///(((((((///**,,,,,,*,*&%///(#*,*************\((/*,,****(//(/(((/(*,***(#,,,*,*,,,,,,,,,,,,.....
////(%(///*,,,,,,,,**,*,,*%*\////*******,,,****\/((/,,*,,,*,,///*,,,,,,,,**(#/,,*,,,,,,,,,,,,,.....
//////,,,,,,,,,,,*,*,,*,**,(//*@********,,,,*\////,,,,,,,,,,,,,,,,,,,,,,,,,/#/,,,,,*,,,,,,,,.......
,..,,.,,,,,,,,,,,*,*,,,*,,**\////****,,,,,,,,**\,,....@.,......,...,...,,,,,,,/#*,,,,,,,,,,,.,.....
...,#..,,,,,,,,,,,,,,,,,*,/,*****,(,,,,,,.,,,.......,,,&@@(** ....,,.,.,,,,,,,,*(%(*,,,,,,,,,,.....
.....,,./#&@@@@@@@@%%@@@&**,,,,,,,,,,,,,.,,.....,,,,/#@&@@%(*,*@@,,,,,,,,,,,,,*,,,,//,,,,,,,,.,....
..,(#####%%&&&&@@@@@@//(/,,,,,,,,,,,,,,,,,,/,,,,,,,,,,,,,,,,(@@&%@@,,,,,,,,,,,,,,,****#%,,,#,......
///////((#%%&&&&&&&@@*********,,,,,,,,,,,,,,,,,,,,,,,,,/@@@@&#@@%(&,,,,,,,,,,,,,,,,,,,**,,,,.,.....
/,,*,,///(###(##%&&&&&%***,,,,,,,,,,,,,,,,,,,,,,,,,,,/%&&@%(&@@%//(@/,,,,,,,,,,,,,,,,,,,,//(.......
,,,...,./////(##%###%(/*****,,,,,,,,,,,,,,,,,,,,,,,,,/(@#,#&@#*,(%@,,,,,,,,,,,,*,,,,.,..,.,,*(,....
... ..,*,,////((((((/**,**,,,,,,,,,,,,,,,,,,,,,,,,,,***(#@/,*((##,,,,*.,,,,,,,,,,..,..,,....,,/,...
......,,.,,////////**,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,%,,*****(,,,,(,,,,,,,,,.,,..,...........,,,,


Idea is to chain functions, in the way, that return value from one function, is propagated as input value to next function
in "function chain". Function, that have been returned, is an anonimus function, composed from arguments, that can be used
as a regular function. Only first function in chain gets the argument(s) when constructed function is used,
and rest of them will take the output from previous, and consider it as an input to themself.
SuperFunction templates only differ from number of arguments, that first function in chain should be called with.
Supported ones(here) are : 0,1 and 2 arguments.
NOTE:  SuperFunction can take for arguments everything what is CALLABLE:
- pointers to regular functions,
- funtional classes (classes that have operator() overrided)
- lambda functions
- std::function
etc

And to make things spicy, you can create SuperFunction from two or more SuperFunctions!
*/

/****************************
	SuperFunction template begin
*****************************/

// SuperFunction0 template

template<typename F, typename... fs>
auto Helper0(const F& func, const fs&... functions)
{
	return func(Helper0(functions...));
}

template<typename F>
auto Helper0(const F& function)
{
	return function();
}

template<typename... Fs>
auto SuperFunction0(const Fs&... functions)
{
	return [&]() {return Helper0(functions...); };
}

// SuperFunction1 template

template<typename Inparam, typename F, typename... fs>
auto Helper1(Inparam input, const F& func, const fs&... functions)
{
	return func(Helper1<Inparam>(input, functions...));
}

template<typename Inparam, typename F>
auto Helper1(Inparam input, const F& function)
{
	return function(input);
}

template<typename Inparam, typename... Fs>
auto SuperFunction1(const Fs&... functions)
{
	return [&](Inparam input) {return Helper1<Inparam>(input, functions...); };
}

//superFunction2 template

template<typename Inparam1, typename Inparam2, typename F, typename... fs>
auto Helper2(Inparam1 input1, Inparam2 input2, const F& func, const fs&... functions)
{
	return func(Helper2<Inparam1, Inparam2>(input1, input2, functions...));
}

template<typename Inparam1, typename Inparam2, typename F>
auto Helper2(Inparam1 input1, Inparam2 input2, const F& function)
{
	return function(input1, input2);
}

template<typename Inparam1, typename Inparam2, typename... Fs>
auto SuperFunction2(const Fs&... functions)
{
	return [&](Inparam1 input1, Inparam2 input2) {return Helper2<Inparam1, Inparam2>(input1, input2, functions...); };
}

/****************************
	SuperFunction template end
*****************************/

/****************************
	Demo Helpers begin
*****************************/
class PlusPlus
{
public:
	int operator()(int number) const
	{
		return number + 1;
	}
};

int Echo(int x)
{
	return x;
}

class TestClass
{
public:
	int GetMagicNumber() const
	{
		return 333;
	}
};

/****************************
	Demo Helpers end
*****************************/

/****************************
	Showcase on specific problem
*****************************/

/*
Lets showcase  the SuperFunctions on next problem

Task:
	Write a program which reads words from standard input and remove consecutive repetition of same word.
	After that, all words should be printed on standard output, in new line each

Test case:
Input:
	c++ python c# c# c# c++ c++
Output:
	c++ python c# c++
*/

void Solve()
{
	auto read = [](std::istream& stream) {
		std::istreambuf_iterator<char> begin(stream), end;
		std::string s(begin, end);
		return s;
	};

	auto separateWords = [](const std::string& in)
	{
		std::vector<std::string> words;
		std::istringstream stringStream(in);
		std::string word;
		while (stringStream >> word)
		{
			words.push_back(word);
		}
		return words;
	};

	auto removeAdjDuplicates = [](std::vector<std::string> words)
	{
		if (words.size() == 0)
		{
			return std::vector<std::string>{};
		}

		// Why to use std::begin and std::end free functions for containers
		// https://stackoverflow.com/questions/8452130/when-to-use-stdbegin-and-stdend-instead-of-container-specific-versions?noredirect=1&lq=1

		std::vector<std::string> filteredWords{ words.front() };
		return std::inner_product(std::cbegin(words), std::cend(words) - 1, std::cbegin(words) + 1, filteredWords,
			[](std::vector<std::string>& acc, const std::string& word)
		{
			if (!word.empty())
			{
				acc.push_back(word);
			}
			return acc;
		},
			[](const std::string& str1, const std::string& str2)
		{
			if (str1 != str2)
			{
				return str2;
			}
			else
			{
				return std::string();
			}
		});
	};

	auto writeVector = SuperFunction2<std::ostream&, std::vector<std::string>>(
		[](std::ostream& out, std::vector<std::string> input)
	{
		// Loops: good and bad https://stackoverflow.com/questions/14373934/iterator-loop-vs-index-loop
		// Make your class range-based https://stackoverflow.com/questions/8164567/how-to-make-my-custom-type-to-work-with-range-based-for-loops

		for (const auto& str : input)
		{
			out << str << std::endl;
		}
	});

	writeVector(std::cout, SuperFunction1<std::istream&>(removeAdjDuplicates, separateWords, read)(std::cin));
}

int main()
{
#ifdef SHOW_EXAMPLES
	auto superFunction1 = SuperFunction1<int>([](int y) {return y * 2; }, [](int x) {return x + 1; });
	std::cout << "SuperFunction1 call: " << superFunction1(5) << std::endl;

	const PlusPlus pp;
	auto superFunction2 = SuperFunction1<int>(pp);
	std::cout << "SuperFunction2 call: " << superFunction2(123) << std::endl;

	TestClass t;
	auto superFunction3 = SuperFunction1<TestClass>(Echo, [](TestClass& x) {return x.GetMagicNumber(); });
	std::cout << "SuperFunction3 call: " << superFunction3(t) << std::endl;

	auto superFunction4 = SuperFunction1<std::string>(Echo, pp, [](std::string& x) {return static_cast<int>(x.size()); });
	std::cout << "SuperFunction4 call: " << superFunction4("teststring") << std::endl;

	auto superFunction5 = SuperFunction1<std::string>(superFunction1, superFunction4);
	std::cout << "SuperFunction5 call: " << superFunction5("teststring") << std::endl;
#endif //SHOW_EXAMPLES

	std::cout << "This is program which reads words from standard input and remove consecutive repetition of same word." << std::endl;
	std::cout << "Example of test case" << std::endl;
	std::cout << "\t Input: c++ python c# c# c# c++ c++" << std::endl;
	std::cout << "\t Output: c++ python c# c++" << std::endl;
	std::cout << "**** User input begin ****" << std::endl;
	Solve();

	return 0;
}