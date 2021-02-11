  #include <CUnit/CUnit.h>
  #include <CUnit/Basic.h>
  #include "hello_functions.h"
  
  void test_add(void) {
    CU_ASSERT(add(2,2) == 4); //what is CU_assert? is it part of CUnit? so what does it do?
    CU_ASSERT(add(0,0) == 0);
    CU_ASSERT(add(-1,1) == 0);
  }
  
  void test_temp_c_to_f(void) {
    float inputs[] = {-40.0, 0.0, 25.0, 100.0};
    float expected_outputs[] = { -40.0, 32.0, 77.0, 212.0};
    
    float tolerance = 0.1;
    
    //num_tests = size of array
    int num_tests = sizeof(inputs)/sizeof(inputs[0]);
    
    int i = 0;
    
    for(i = 0; i < num_tests; i++) {
        CU_ASSERT(temp_c_to_f(inputs[i]) >= expected_outputs[i] - tolerance);
       
        CU_ASSERT(temp_c_to_f(inputs[i]) <= expected_outputs[i] + tolerance);
    }
  }
  
  void test_temp_sensor_to_c_valid(void){
    bool success = false;

    int inputs[] = {0, 511, 1023};
    float expected_outputs[] = {-55.0, 34.9, 125.0};

    float tolerance = 0.1;

    //num_tests has number of elements in inputs array
    int num_tests = sizeof(inputs)/sizeof(inputs[0]); 

    int i = 0;

    for(i = 0; i < num_tests; i++){
        CU_ASSERT(temp_sensor_converter(inputs[i], &success) >= expected_outputs[i] - tolerance);
        CU_ASSERT(success == true); 

        CU_ASSERT(temp_sensor_converter(inputs[i], &success) <= expected_outputs[i] + tolerance);
        CU_ASSERT(success == true); 
    }
}

void test_temp_sensor_to_c_invalid(void){
    int inputs[] = {-100, -1, 1024, 1100};
    float expected_outputs[] = {-100.0, -100.0, -100.0, -100.0};
    bool success = true;
    
    float tolerance = 0.1;

    //num_tests has number of elements in inputs array
    int num_tests = sizeof(inputs)/sizeof(inputs[0]); 

    int i = 0;

    for(i = 0; i < num_tests; i++){
        CU_ASSERT(temp_sensor_converter(inputs[i], &success) >= expected_outputs[i] - tolerance);
        CU_ASSERT(success == false); 

        CU_ASSERT(temp_sensor_converter(inputs[i], &success) <= expected_outputs[i] + tolerance);
        CU_ASSERT(success == false); 
    } 
}
    

int main(){
    CU_initialize_registry();
    
    CU_pSuite suite1 = CU_add_suite("test_add", 0, 0);
    CU_pSuite suite2 = CU_add_suite("test_temp_c_to_f", 0, 0);
    CU_pSuite suite3 = CU_add_suite("test_temp_sensor_to_c_valid", 0, 0);
    CU_pSuite suite4 = CU_add_suite("test_temp_sensor_to_c_invalid", 0, 0);
    
    CU_add_test(suite1, "test_add", test_add);
    CU_add_test(suite2, "test_temp_c_to_f", test_temp_c_to_f);
    CU_add_test(suite3, "test_temp_sensor_to_c_valid", test_temp_sensor_to_c_valid);
    CU_add_test(suite4, "test_temp_sensor_to_c_invalid", test_temp_sensor_to_c_invalid);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();

    CU_cleanup_registry();



    return 0;
    
}
