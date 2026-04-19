# Solutions Manual
### *Data Structures & Algorithm Analysis in C++* — Clifford A. Shaffer

## ✦ What This Is

This repository contains full solutions to every **exercise** and **project** in Clifford A. Shaffer's *Data Structures and Algorithm Analysis in C++*.

Each chapter is treated as its own self-contained module:

- **Exercises** → typeset as clean, structured **LaTeX PDFs**, with proofs written carefully and code fragments formatted properly
- **Projects** → implemented as **compilable, well-documented C++ executables**, organized with CMake and tested

The goal is not just to have answers — it's to have *good* answers. Ones that actually explain the reasoning.


## 📖 Progress

| Chapter | Title | Exercises | Projects |
|:-------:|-------|:---------:|:--------:|
| 1 | Data Structures and Algorithms | ✅ Complete | ✅ Complete |
| 2 | Mathematical Preliminaries | ✅ Complete | ✅ Complete |
| 3 | Algorithm Analysis | ✅ Complete | ✅ Complete |
| 4 | Lists, Stacks, and Queues | 🔄 In Progress | ⬜ Not Started |
| 5 | Binary Trees | ⬜ Not Started | ⬜ Not Started |
| 6 | Non-Binary Trees | ⬜ Not Started | ⬜ Not Started |
| 7 | Internal Sorting | ⬜ Not Started | ⬜ Not Started |
| 8 | File Processing and External Sorting | ⬜ Not Started | ⬜ Not Started |
| 9 | Searching | ⬜ Not Started | ⬜ Not Started |
| 10 | Indexing | ⬜ Not Started | ⬜ Not Started |
| 11 | Graphs | ⬜ Not Started | ⬜ Not Started |
| 12 | Lists and Arrays Revisited | ⬜ Not Started | ⬜ Not Started |
| 13 | Advanced Tree Structures | ⬜ Not Started | ⬜ Not Started |
| 14 | Analysis Techniques | ⬜ Not Started | ⬜ Not Started |
| 15 | Limits to Computation | ⬜ Not Started | ⬜ Not Started |

> ✅ Complete · 🔄 In Progress · ⬜ Not Started

---

## 🛠 Building the C++ Projects

All projects use **CMake** and require a **C++17** compatible compiler.

### Prerequisites

- CMake ≥ 3.16
- A C++17 compiler (GCC 9+, Clang 10+, or MSVC 2019+)

### Build All Projects

```bash
git clone https://github.com/YOUR_USERNAME/dsa-shaffer-solutions.git
cd dsa-shaffer-solutions

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Build a Specific Chapter

```bash
cmake -S chapter-03 -B build/ch03
cmake --build build/ch03
```

### Run a Project

```bash
./build/chapter-01/projects/project_1_1/project_1_1
```

---

## 📄 Compiling the LaTeX PDFs

Each chapter's exercise PDF can be compiled independently. All chapters share a common preamble from `latex/preamble.tex`.

### Prerequisites

- A LaTeX distribution: [TeX Live](https://tug.org/texlive/) (Linux/macOS) or [MiKTeX](https://miktex.org/) (Windows)

### Compile a Single Chapter

```bash
cd chapter-01/exercises
pdflatex ch01_exercises.tex
```

### Compile All Chapters (Bash)

```bash
for dir in chapter-*/exercises; do
  (cd "$dir" && pdflatex *.tex)
done
```

Pre-compiled PDFs are committed to the repository — you can read them directly without a LaTeX installation.

---

## 📐 LaTeX Style and Conventions

Exercise PDFs follow a consistent structure:

- Each exercise is numbered to match the book exactly (e.g. **Exercise 3.4**)
- Proofs use formal notation where appropriate
- Code fragments in exercises are typeset with syntax highlighting via the `listings` package
- Each PDF opens with a brief chapter summary to provide context

The shared preamble (`latex/preamble.tex`) defines all custom macros, colour schemes, and environments so every chapter looks identical.

---

## ⚙️ C++ Conventions

All project code follows a consistent style:

- **Standard:** C++17
- **Formatting:** `clang-format` with Google style (`.clang-format` included)
- **Build system:** CMake with a shared `CompilerFlags.cmake` (warnings enabled: `-Wall -Wextra -Wpedantic`)
- **No external dependencies** — only the C++ standard library
- Each project has its own `README.md` explaining what it implements and how to run it

---

## 🤝 A Note on Use

These solutions are written as a **learning resource** — the kind of thing I wish existed when working through the book. They are written from a student's perspective, with the goal of understanding, not just answering.

If you find an error, a cleaner approach, or a missing edge case:

1. Open an **Issue** describing the problem
2. Or submit a **Pull Request** with a fix

All corrections are genuinely appreciated.

---

## 📚 About the Book

> *Data Structures and Algorithm Analysis in C++*, 3rd Edition  
> Clifford A. Shaffer — Virginia Tech  
> Published by Dover Publications

The book is freely available as a PDF from the author's website at:  
**[people.cs.vt.edu/shaffer/Book/](https://people.cs.vt.edu/shaffer/Book/)**

---

## 📜 License

This repository is licensed under the **MIT License**.  
The solutions are original work. The book itself is © Clifford A. Shaffer.

---

<div align="center">

*Built with patience, caffeine, and an irrational love of binary trees.*

⭐ If this helps you, a star is always appreciated.

</div>
