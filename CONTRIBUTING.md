# Guidelines for Contributing to C++ Projects

Welcome to the team! Please adhere to the following guidelines to contribute effectively to the project.

## Version Control

1. Use Git as the version control system.
2. Work in a separate branch and create pull requests for your changes.
3. Ensure that your code is clean and well-documented before creating pull requests.
4. Use meaningful commit messages to describe your changes.

## Indentation and Line Length

### Indentation

- Always use tabs for indentation.
- One tab is equivalent to 4 spaces.

### Line Length

- Limit the line length to a maximum of 72 characters.
- Break the line if it exceeds the maximum length.

### Font

- Use a monospaced font where each character has the same width.

### IDE Settings

- Configure your IDE to adhere to the above formatting conventions.

## Method and File Size

Violation of the following limits or rules necessitates splitting the object.

### Method Size

- Maximum of 5 statements per function.
- Maximum of 40 lines per function.

### File Length

- 20 to 100 lines per file.
- Maximum of 500 lines per file.
- One class per file.

### Size Checks

- Reconsider architecture if over 1000 lines.

## Brackets and Spaces

### Bracket Placement

- Opening bracket on the same line as the keyword.
- Code within curly braces `{}` indented.
- Include brackets even for single statements.
- Closing curly braces `}` placed on the same indentation level as the keyword.
- After a closing curly brace `}`, insert a line break.

### Spaces

- No space before or after the opening bracket.
- Space after the closing bracket, but not before.
- Space after the comma in lists, but not before.

### Blank Lines

- Insert a blank line after each opening curly brace `{`.
- Insert a blank line before each line containing a single-line comment `//`.
- Insert a blank line before each `return` statement.

## Identifiers

### Variables

- Identifier in `camelCase`.
- Begins with the object it describes, followed by various adjectives for description.

### Constants, Enum Elements, and Macros

- Written in `SCREAMING_SNAKE_CASE`.

### Class Names

- Written in `PascalCase`.

### Method Identifiers

- Written in `camelCase`.
- Always begins with a verb.

### Class Attributes

- Named in `snake_case`.
- Follow the same rules as variables.

### Custom Data Types of All Kinds

- Named in `skewer-case`.
- The identifier follows `nocase` rules.
- Object comes first followed by the type.

### Everything Else... fuck it!

- Written in `fUcKtHeCaSe`.

## Header

Ensure that headers are not included multiple times.

## Documentation

Before each Funktion, Method, Class or at the file beginning.
Generate a Commentblock with @tags for doxygen.

We want to generate the documentation automaticly, please make sure you hit the doxygen syntax.

## Pull Requests

1. Clearly describe what your pull request accomplishes and what issues it resolves.
2. Include screenshots, code examples, or other relevant information to illustrate your changes if necessary.
3. Request review from other team members before merging the pull request.

## Communication

1. Stay updated on project changes.
2. Communicate clearly and respectfully in team chats or discussions on pull requests.

## Feedback

1. Provide constructive feedback on pull requests from other team members.
2. Be open to suggestions and discussions about code or process improvements.

---

Thank you for your contributions!
