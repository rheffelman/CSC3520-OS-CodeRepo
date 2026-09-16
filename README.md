# Operating Systems: Starter Environment

We will be using GitHub Codespaces to ensure everyone has a standard Linux environment for system calls like `fork()`, `exec()`, and `pthreads`.

## Launching Your Workspace

1. Click the green **Use this template** button at the top of this page to generate your own copy of this repository.
2. Navigate to your new repository, click the green **Code** button.
3. Switch to the **Codespaces** tab and click **Create codespace on main**.
4. Wait a few moments for the browser-based VS Code editor to load your Linux container.

## Setting Up GitHub Codespaces

A codespace is a Linux machine running in the cloud with VS Code served to your browser. It works the same on Windows, Mac, and Chromebooks, so everyone in the class will have an identical environment.

You will need a GitHub account. If you don't have one, create one with your Carthage email address. Then, apply for the GitHub Student Developer Pack at https://education.github.com/pack. Verification requires proof that you are a student, like a school email address or a photo of your student ID, and it can take a few days to be approved. Do not wait until the night before an assignment is due to do this.

Getting verified matters because Codespaces is free only up to a monthly limit. A regular free account gets 60 hours per month on the smallest machine. A verified student account gets 90 hours per month plus extra storage. That is more than enough for this course, but only if you manage it.

The most important habit: stop your codespace when you are done working. A codespace uses up your monthly hours whenever it is running, even if you are not typing. It will stop itself after 30 minutes of inactivity, but a forgotten browser tab can quietly eat your quota. Your files are saved when a codespace stops, so you lose nothing by stopping it. You can see and stop all of your codespaces at https://github.com/codespaces.

One last thing. Codespaces requires an internet connection. If your connection is unreliable, plan to do your work on campus or somewhere with stable wifi. Running out of hours or losing your connection the night before a deadline is not an excused reason for late work, so build in some slack.

## Compiling Your Code

Once your editor is open, you will need to use the terminal to compile your C++ code. 

1. Open the integrated terminal by clicking **Terminal > New Terminal** in the top menu (or pressing `` Ctrl + ` ``).
2. To compile `main.cpp`, type the following command and press Enter:
   
```bash
g++ main.cpp -o os_program
```
