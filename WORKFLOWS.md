# GitHub Actions Workflows Guide

This document provides detailed information about all GitHub Actions workflows in this project.

## Overview

This project includes 6 comprehensive GitHub Actions workflows that demonstrate modern CI/CD practices for C++ projects:

1. **CI** - Core build and test workflow
2. **Code Coverage** - Track test coverage metrics
3. **CodeQL Security Scan** - Automated security analysis
4. **Documentation** - Generate and deploy API documentation
5. **Release** - Automated release creation with artifacts
6. **Compiler Compatibility** - Multi-compiler testing

## Workflow Details

### 1. CI Workflow (ci.yml)

**Purpose**: Core continuous integration workflow for building and testing across platforms.

**Triggers**:
- Push to `main`, `master`, or `develop` branches
- Pull requests to `main` or `master`

**Build Matrix**:
- Platforms: Ubuntu, macOS, Windows
- Build Types: Debug, Release
- Total: 6 combinations

**Key Features**:
- Platform-specific environment setup
- CMake build caching for faster builds
- Parallel compilation (-j 4)
- Automated testing with CTest
- Artifact uploads for binaries and libraries

**Outputs**:
- Build artifacts for each platform/configuration
- Test results

---

### 2. Code Coverage Workflow (code-coverage.yml)

**Purpose**: Generate and track code coverage metrics.

**Triggers**:
- Push to `main`, `master`, or `develop` branches
- Pull requests to `main` or `master`

**Key Features**:
- Compiles with coverage flags (--coverage)
- Generates coverage reports using lcov
- Uploads to Codecov (optional, requires CODECOV_TOKEN)
- Creates HTML coverage reports
- Comments on PRs with coverage percentage
- Checks 80% coverage threshold (warning only)

**Outputs**:
- coverage.info (lcov format)
- HTML coverage report (artifact)
- Codecov integration (if configured)

**Setup Required**:
1. (Optional) Sign up at https://codecov.io
2. (Optional) Add `CODECOV_TOKEN` to repository secrets

---

### 3. CodeQL Security Scan (codeql.yml)

**Purpose**: Static Application Security Testing (SAST) for vulnerability detection.

**Triggers**:
- Push to `main`, `master`, or `develop` branches
- Pull requests to `main` or `master`
- Scheduled: Every Monday at 2:00 AM UTC
- Manual dispatch

**Key Features**:
- Scans C++ code for security vulnerabilities
- Uses security-and-quality query set
- Integrates with GitHub Security tab
- Detects: buffer overflows, memory leaks, SQL injection, etc.
- Generates SARIF reports

**Outputs**:
- Security alerts in GitHub Security tab
- SARIF report artifacts

**No Setup Required**: Works out of the box with GitHub

---

### 4. Documentation Workflow (documentation.yml)

**Purpose**: Generate API documentation and deploy to GitHub Pages.

**Triggers**:
- Push to `main` or `master` branch
- Manual dispatch (workflow_dispatch)

**Key Features**:
- Generates Doxygen documentation automatically
- Creates call graphs and class diagrams (Graphviz)
- Auto-generates Doxyfile if not present
- Deploys to GitHub Pages
- Checks for undocumented APIs
- Provides documentation quality metrics

**Outputs**:
- HTML documentation deployed to GitHub Pages
- Documentation artifact

**Setup Required**:
1. Enable GitHub Pages in repository settings
2. Set Pages source to "GitHub Actions"
3. Documentation will be available at: `https://YOUR_USERNAME.github.io/action-demo/`

---

### 5. Release Workflow (release.yml)

**Purpose**: Automated release creation with multi-platform binaries.

**Triggers**:
- Push of version tags (v*.*.*)
- Manual dispatch with version input

**Key Features**:
- Builds release binaries for Linux, macOS, Windows
- Generates release notes from commit history
- Groups changes by type (feat, fix, docs, etc.)
- Creates SHA256 checksums for verification
- Uploads platform-specific archives
- Supports manual version override

**Outputs**:
- GitHub Release with auto-generated notes
- Linux binaries (tar.gz)
- macOS binaries (tar.gz)
- Windows binaries (zip)
- SHA256 checksums for all archives

**Usage Example**:
```bash
# Create and push a version tag
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0

# Or use workflow_dispatch from GitHub Actions UI
```

**Commit Message Conventions**:
- `feat:` - New features
- `fix:` - Bug fixes
- `docs:` - Documentation changes
- `chore:` - Maintenance tasks
- `refactor:` - Code refactoring
- `test:` - Test additions/changes

---

### 6. Compiler Compatibility Workflow (compiler-compatibility.yml)

**Purpose**: Ensure code compiles across multiple compilers and C++ standards.

**Triggers**:
- Push to `main` or `master`
- Pull requests to `main` or `master`
- Scheduled: Every Sunday at 3:00 AM UTC
- Manual dispatch

**Test Matrix**:

**GCC Versions** (using Docker containers):
- GCC 9, 10, 11, 12, 13
- C++ Standards: C++17, C++20
- Note: GCC 9 excluded from C++20 tests (limited support)

**Clang Versions**:
- Clang 12, 13, 14, 15, 16
- C++ Standards: C++17, C++20

**MSVC Versions**:
- MSVC 2019 (Windows Server 2019)
- MSVC 2022 (Windows Server 2022)
- C++ Standards: C++17, C++20

**Key Features**:
- Uses Docker for consistent GCC environments
- Tests across 30+ compiler/standard combinations
- Provides compatibility summary
- Identifies compiler-specific issues early

**Outputs**:
- Build status for each compiler combination
- Compatibility summary report

---

## Workflow Status Badges

Add these to your README.md (replace YOUR_USERNAME with your GitHub username):

```markdown
[![CI](https://github.com/YOUR_USERNAME/action-demo/workflows/CI/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![Code Coverage](https://github.com/YOUR_USERNAME/action-demo/workflows/Code%20Coverage/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![CodeQL](https://github.com/YOUR_USERNAME/action-demo/workflows/CodeQL%20Security%20Scan/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![Documentation](https://github.com/YOUR_USERNAME/action-demo/workflows/Documentation/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![Compiler Compatibility](https://github.com/YOUR_USERNAME/action-demo/workflows/Compiler%20Compatibility/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
```

## Resource Management

### GitHub Actions Minutes

Free tier provides 2,000 minutes/month for private repositories (unlimited for public).

**Estimated Usage per Push**:
- CI: ~30 minutes (6 jobs × ~5 min)
- Code Coverage: ~5 minutes
- CodeQL: ~10 minutes
- Compiler Compatibility: ~90 minutes (30+ jobs × ~3 min)
- Documentation: ~3 minutes
- **Total: ~138 minutes per push**

**Optimization Tips**:
1. Disable Compiler Compatibility on every push (use schedule/manual only)
2. Use path filters to skip workflows when irrelevant files change
3. Leverage caching to reduce build times
4. Run expensive workflows only on main branch

### Workflow Optimization

To reduce CI minutes, consider:

1. **Path Filters** - Only run workflows when relevant files change:
```yaml
on:
  push:
    paths:
      - 'src/**'
      - 'tests/**'
      - 'CMakeLists.txt'
```

2. **Branch Restrictions** - Run expensive workflows only on main:
```yaml
on:
  push:
    branches: [ main ]
```

3. **Conditional Jobs** - Skip jobs based on commit messages:
```yaml
if: "!contains(github.event.head_commit.message, '[skip ci]')"
```

## Troubleshooting

### Common Issues

**1. Code Coverage not uploading to Codecov**
- Ensure `CODECOV_TOKEN` is set in repository secrets
- Check that coverage.info file is generated
- Workflow continues even if Codecov fails (fail_ci_if_error: false)

**2. Documentation not deploying**
- Verify GitHub Pages is enabled in repository settings
- Check that Pages source is set to "GitHub Actions"
- Ensure workflow has `pages: write` permission

**3. Release workflow fails**
- Verify tag format matches `v*.*.*` pattern
- Ensure GITHUB_TOKEN has necessary permissions
- Check that binaries are being built correctly

**4. Compiler Compatibility timeout**
- Some compiler installations may take time
- Consider reducing the compiler matrix
- Use scheduled runs instead of on every push

## Best Practices

1. **Keep workflows focused** - Each workflow has a single responsibility
2. **Use caching** - Cache dependencies and build artifacts
3. **Fail fast** - Set `fail-fast: false` to see all failures
4. **Provide feedback** - Use PR comments and step summaries
5. **Document workflows** - Include comments in YAML files
6. **Test locally** - Use act or similar tools to test workflows locally
7. **Monitor usage** - Check Actions usage in repository insights

## Additional Resources

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [CMake Documentation](https://cmake.org/documentation/)
- [Google Test Documentation](https://google.github.io/googletest/)
- [Codecov Documentation](https://docs.codecov.com/)
- [CodeQL Documentation](https://codeql.github.com/docs/)
- [Doxygen Documentation](https://www.doxygen.nl/manual/)

## Contributing

When adding new workflows:

1. Create workflow file in `.github/workflows/`
2. Test thoroughly before merging to main
3. Update this documentation
4. Add status badge to README.md
5. Consider resource usage and optimization
