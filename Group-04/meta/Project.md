## <span id="group-4" style="color: blue">Group 4: Torvalds</span>

**Members**: Chris Paul, Grant Davis, Krishna Patel, Kyle Gunger, and Rose Spangler

**Shared Interests**: Scripting Language / Data Processing

**Notable Strengths**: Algorithms, Compilers, Software Engineering

### Classes to Build

| Class               | Description |
| ------------------- | ----------- |
| **`BitVector`**     | Similar to [`std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset), but allows for size changing.  Ideally, [`std::vector<bool>`](https://en.cppreference.com/w/cpp/container/vector_bool) should fill the role in the standard library, but it doesn't have the extra functionality for bitwise operations that would make having a BitVector so useful. |
| **`IndexSet`**      | A collection of indices from another container.  This is a quick way to track sets of indices, for example those that have a special property.  A simple way of implementing this functionality is simply keeping a set of indices, but faster options could be tracking ranges of indices (e.g., 106-112, 152-225) if they are clustered, or using a BitVector if they are not. |
| *Audited String* | Functionality of [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string), but when compiled in debug mode, checks every index to ensure it is valid and in range; similar checks for iterators.  You can make your `cse::String` derive from `std::string` to get started (e.g., `class String : public std::string`). In functions that you need to simply pass a call to the base type, this is easy to do: `String & clear() noexcept { std::string::clear(); return *this; }`.  You can also add any other member functions that you think would be useful to have work on strings.  For a more advanced version, you should create a `cse::BasicString` that allows you to specify character types.  |
| **`Text`**          | A string-like object that also tracks formatting of the string (such as bold, italic, colors, maybe even links).  Ideally it should come with functions like `ToHTML()` or `ToLatex()` to convert to a string in the correct format. |
| **`Assert`**        | A better version of "assert" than the one supplied by "assert.h", perhaps calling it cse_assert instead. Your new version should be able to print targeted messages as well as the current value of supplied variables.  Ideally, you should be able to have something like `cse_assert(x < 200, "Outside of Bounding Box!");` and if the assert gets triggered it should print an error like `Assert error in "filename" on line X: Outside of Bounding Box! (x = 255).` NOTE: You will need to learn about macros to make an effective assert. |

### Application Suggestion

A **rich text translation app**. Translate between a pair of formats; some to chose from include HTML, Latex, Markdown, RTF, Docx (MS Word), or ANSI.  Include warnings when formats can't translate cleanly (e.g., ANSI can't handle links)

Suggested **challenges**: Add more than two targets so that the user specifies on the command line what they want to do.  Or make your own flexible format (if you like this direction, Dr. Ofria can provide more ideas).  Or even make this a web app for doing the translation.
