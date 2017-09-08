#include "../main.h"

void work_choiceDirect(){
	static int8_t status = 0;
	if(((system.statusHallL == 1) || (system.statusHallR == 1)) && status == 0){
		SoftStop();
		status = 1;
	}
	if(status==1){
		system.DD = !(system.DD);
		status = 2;
	}
	if(system.statusHallL == 0 && system.statusHallR == 0 && status == 2)
	status = 0;

}
void work_serva_R(){
	system.step++;
	Move(system.DD,STEP_SERVA);
}
void work_serva_L(){
	system.step--;
	Move(!(system.DD), STEP_SERVA);
}