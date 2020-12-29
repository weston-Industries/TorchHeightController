#ifndef TORCHHEIGHT_H_ /* Include guard */
#define TORCHHEIGHT_H_

void process(); //Calulates position and move steps
void trigger0(); //Set last page used on startup loaded event
void trigger1(); //read customsetpoint on page loaded event
void trigger2(); //Save customsetpoints on end touch event
void trigger3(); //Move motor up
void trigger4(); //Move motor down
void trigger5(); //Increase allowable down movement range
void trigger6(); //Decrease allowable up movement range
void trigger7(); //Increase allowable up movement range
void trigger8(); //Decrease allowable down movement range
void trigger9(); //Increase voltage gap between aggressive and normal targeting
void trigger10(); //Decrease voltage gap between aggressive and normal targeting
void trigger11(); //Increase voltage reading threshold for calculating movements
void trigger12(); //Decrease voltage reading threshold for calculating movements
void trigger13(); //Increase delay before calculating movements
void trigger14(); //Decrease delay before calculating movements
void trigger15(); //Increase steps per millimeter
void trigger16(); //Decrease steps per millimeter
void trigger17(); //Increase Aggressive P Parameter
void trigger18(); //Decrease Aggressive P Parameter
void trigger19(); //Increase Aggressive I Parameter
void trigger20(); //Decrease Aggressive I Parameter
void trigger21(); //Increase Aggressive D Parameter
void trigger22(); //Decrease Aggressive D Parameter
void trigger23(); //Increase Conservative P Parameter
void trigger24(); //Decrease Conservative P Parameter
void trigger25(); //Increase Conservative I Parameter
void trigger26(); //Decrease Conservative I Parameter
void trigger27(); //Increase Conservative D Parameter
void trigger28(); //Decrease Conservative D Parameter
void trigger29(); //load movement page settings
void trigger30(); //Load default page settings
void trigger31(); //Save Scale on end touch event
void trigger32(); //Load Aggressive PID settings
void trigger33(); //Load Conservative PID Settings
void trigger34(); //Load Calibration Offset
void trigger35(); //Save Calibration Offset on end touch event
void report(); //report plasma voltage and position
void format(); //Set text color

#endif // TORCHHEIGHT_H_