#include <iostream>
#include <assert.h>

// Global variable to count alert failures
int alertFailureCount = 0;

// Declare a function pointer type for network alert
typedef int (*NetworkAlertFunc)(float);

// Stub function for testing
int networkAlertStub(float celcius) {
    std::cout << "ALERT: Temperature is " << celcius << " celcius.\n";
    // Stub always returns 500 for failure (simulate alert failure)
    return 500;
}

// Real function for production (for demonstration purposes)
int realNetworkAlert(float celcius) {
    std::cout << "Sending real alert for temperature: " << celcius << " celcius.\n";
    // Return 200 for ok and 500 for failure
    return (celcius > 200.0) ? 500 : 200;
}

// Function to alert based on temperature, with injected network alert function
void alertInCelcius(float farenheit, NetworkAlertFunc networkAlert) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlert(celcius);
    if (returnCode != 200) {
        // Increment failure count on failure
        alertFailureCount += 1;
    }
}

int main() {
    // Test environment using the stub
    alertInCelcius(400.5, networkAlertStub);  // This should fail
    alertInCelcius(303.6, networkAlertStub);  // This should fail

    assert(alertFailureCount == 2);
    
    alertInCelcius(150.0, realNetworkAlert);  // This should pass
    alertInCelcius(400.5, realNetworkAlert);  // This should fail

    assert(alertFailureCount == 3);
    std::cout << alertFailureCount << " alerts failed in production environment.\n";
    std::cout << "All is well (maybe!)\n";
    return 0;
}
