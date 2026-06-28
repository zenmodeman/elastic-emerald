# AGENTS.md instructions

When working with the elastic-emerald project, avoid doing build checks unless explicitly asked and stick to static checks for code verification. The developer will handle doing the build check, since the overhead is large and a build can take a long time.

Any new tests created for this project should use the `Zenmodeman: ` prefix in the test name, to distinguish these tests from Expansion native tests.
