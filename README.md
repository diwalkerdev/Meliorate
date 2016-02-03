# Meliorate
Unit test runner for C++.

Aims:
- Minimal, simple, easy to understand. Few or no magics.
- Do not sacrifice the above for backward compatibility.

## Adding tests
Tests are self registering.
```
TEST("this is a simple self-registering test", []() {
});

```

The test runner is executed with:
```
auto main() -> int {
    return Meliorate()->run();
}
```

## Assertions
Meliorate does not provide any assertions. You should use
[snowhouse](https://github.com/banditcpp/snowhouse) assertions instead.
