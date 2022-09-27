#ifndef CEDILLA_CPP_IF
# define CPP_IF_1(...) __VA_ARGS__
# define CPP_IF_0(...)
# define CPP_IF(X, ...) CPP_APPLY(CPP_CONCAT(CPP_IF_, X), ...)
#endif