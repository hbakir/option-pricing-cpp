#include "option_pricing.hpp"

int main() {
    using value_type = double;

    // Instantiate call and put processing policies
    op::Processing<value_type> converter;
    op::ProcessingII<value_type> converter2;

    // Pricing calls
    op::SUD<value_type, op::Input, op::Output> callPricer(converter);
    value_type S = 60.0;
    callPricer.run(S);

    // Pricing puts
    op::SUD<value_type, op::Input, op::Output> putPricer(converter2);
    value_type S2 = 60.0;
    putPricer.run(S2);

    return 0;
}
