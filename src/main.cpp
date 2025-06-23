#include "option_pricing.hpp"

int main() {
    using value_type = double;

    // Instantiate call and put processing policies
    Processing<value_type> converter;
    ProcessingII<value_type> converter2;

    // Pricing calls
    SUD<value_type, Input, Output> callPricer(converter);
    value_type S = 60.0;
    callPricer.run(S);

    // Pricing puts
    SUD<value_type, Input, Output> putPricer(converter2);
    value_type S2 = 60.0;
    putPricer.run(S2);

    return 0;
}