

struct controller {
    char *manipulated_variable;
    char *process_variable;
    float overflow;
    float underflow;
    float ku;
    float pu;
    float kp;
    float ki;
};

struct controller controller_init(char *manipulated_variable, char *process_variable, float overflow, float underflow, float ku, float pu);

float pi_algorithm(struct controller *cont, float reference, float control_variable);

float get_sensor(char *sensor);

void set_actuator(float control_action, char *actuator);
