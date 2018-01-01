#ifndef J_error_H
#define J_error_H

#include<exception>

class J_error : public std::exception
{
public:
  J_error(const char *msg)
    : std::exception(), msg_(msg)
    { }
  virtual const char * what() const throw() { return msg_; }
private:
  const char *msg_;
};

#define DEFINE_EXCEPTION(ClassName,Message) \
    class ClassName : public J_error \
    { \
    public: \
        ClassName(const char *msg = Message) \
            : J_error(msg) \
        { } \
    };

#endif


