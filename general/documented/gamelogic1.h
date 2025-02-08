/**
 * @brief TODO: Describe function.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void emergency();

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void fn_START(void);

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void fn_KEY_WOUT_DOUB(void);

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void fn_KEY_WH_DOUB(void);

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void fn_RESET_TENT(void);

/**
 * @brief TODO: Describe function.
 * @param dim TODO: Describe parameter.
 * @param diff TODO: Describe parameter.
 * @param doubles TODO: Describe parameter.
 * @param tents TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void initGame(int16_t dim, int8_t diff, bool doubles, int16_t tents);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param par1 TODO: Describe parameter.
 * @param par2 TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void allocate_in_Heap_Int(int16_t** array, int16_t par1, int16_t par2);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param par1 TODO: Describe parameter.
 * @param par2 TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void allocate_in_Heap_Char(int8_t** array, int16_t par1, int16_t par2);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param par1 TODO: Describe parameter.
 * @param par2 TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void allocate_in_Heap_Bool(bool** array, int16_t par1, int16_t par2);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void deallocate_Char(int8_t* array);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void deallocate_Int(int16_t* array);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void deallocate_Bool(bool* array);

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int16_t* key_generation_wout_doub(void);

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int16_t* key_generation_wh_doub(void);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param value TODO: Describe parameter.
 * @param dim TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
bool presence_Double(int16_t* array, int16_t value, int16_t dim);

/**
 * @brief TODO: Describe function.
 * @param index TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int8_t int_Conversion_to_Char(int16_t index);

/**
 * @brief TODO: Describe function.
 * @param arr1 TODO: Describe parameter.
 * @param arr2 TODO: Describe parameter.
 * @param dim TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void crypt_sequence_Int_Char(int16_t* arr1, int8_t* arr2, int16_t dim);

/**
 * @brief TODO: Describe function.
 * @param sequence TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void continue_Key_Decryption(int16_t* sequence);

/**
 * @brief TODO: Describe function.
 * @param void TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void resetTentative(void);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param par1 TODO: Describe parameter.
 * @param par2 TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void makeArrayEmpty_Char(int8_t* array, int16_t par1, int16_t par2);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param par1 TODO: Describe parameter.
 * @param par2 TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void makeArrayEmpty_Int(int16_t* array, int16_t par1, int16_t par2);

/**
 * @brief TODO: Describe function.
 * @param array TODO: Describe parameter.
 * @param par1 TODO: Describe parameter.
 * @param par2 TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void makeArrayEmpty_Bool(bool* array, int16_t par1, int16_t par2);