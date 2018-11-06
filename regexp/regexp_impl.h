#pragma once

#include <regexp/regexp.h>

#include "expressions/expression.h"


namespace regexp {

class RegexpImpl : public Regexp {
public:
    explicit RegexpImpl(const std::string& s);

    virtual bool has(const std::string& s) const override;

private:
    std::unique_ptr<expressions::Expression> expression_;
};

} // namespace regexp
