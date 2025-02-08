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
void reset_Screen(void) {
    // Function code
}

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
void graphics_Init(void) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param rect TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int32_t getCenteredX(Graphics_Rectangle rect) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param rect TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int32_t getCenteredY(Graphics_Rectangle rect) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param state TODO: Describe parameter.
 * @param color TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int32_t chooseColorRect(Button_State state, int32_t color) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param state TODO: Describe parameter.
 * @param color TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int32_t chooseColorText(Button_State state, int32_t color) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param state TODO: Describe parameter.
 * @param rect TODO: Describe parameter.
 * @param color TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void focusedhandle(Button_State state, Graphics_Rectangle rect, int32_t color) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @param size TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
int8_t findSelected(Graphics_Button array[], int8_t size) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param button TODO: Describe parameter.
 * @param rect_color TODO: Describe parameter.
 * @param text_color TODO: Describe parameter.
 * @param pos_selected TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void drawButton(Graphics_Button button, int32_t rect_color, int32_t text_color, int8_t pos_selected) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param rect TODO: Describe parameter.
 * @param colorRect TODO: Describe parameter.
 * @param text TODO: Describe parameter.
 * @param colorText TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void rectangleWithText(Graphics_Rectangle rect, int32_t colorRect, Graphics_Text text, int32_t colorText) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @param position TODO: Describe parameter.
 * @param size TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void handleOut(Graphics_Button array[], uint8_t position, int8_t size) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @param position TODO: Describe parameter.
 * @param size TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void handleIn(Graphics_Button array[], uint8_t position, int8_t size) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void hardware_Init() {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void handle_buttons(Graphics_Button array[]) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void handleSelection(Graphics_Button array[]) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void handleDeselection(Graphics_Button array[]) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @param array[] TODO: Describe parameter.
 * @param size TODO: Describe parameter.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void initArray(Graphics_Button array[], int size) {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void acquireMutex() {
    // Function code
}

/**
 * @brief TODO: Describe function.
 * @return TODO: Describe return value.
 * @author Matteo Gottardelli
 * @author Niccolò Cristoforetti
 * @author Alessandro Benassi
 * @author Daniele Calvo
 * @date 2025-02-08
 */
void releaseMutex() {
    // Function code
}