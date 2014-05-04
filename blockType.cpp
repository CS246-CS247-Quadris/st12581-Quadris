#include "blockType.h"

IBlock::IBlock(Cell*** bd, int level) {
    type='I';
    this->level=level;
    x[0] = 0;y[0] = height-4;
    x[1] = 1;y[1] = height-4;
    x[2] = 2;y[2] = height-4;
    x[3] = 3;y[3] = height-4;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}

bool IBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){//clock
        tempStatus=(status + 1)%4;
    }
    else if(type=='C'){//counterclock
        tempStatus=(status - 1)%4;
    }
    
    if (tempStatus%2 == 0) {
        tempX[0] = x[0]; tempY[0] = y[0];
        tempX[1] = x[1]+1; tempY[1] = y[1]-1;
        tempX[2] = x[2]+2; tempY[2] = y[2]-2;
        tempX[3] = x[3]+3; tempY[3] = y[3]-3;
    } else {
        tempX[0] = x[0]; tempY[0] = y[0];
        tempX[1] = x[1]-1; tempY[1] = y[1]+1;
        tempX[2] = x[2]-2; tempY[2] = y[2]+2;
        tempX[3] = x[3]-3; tempY[3] = y[3]+3;
    }
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}



/*-----------------------------------------------------------------------------------------------------------------------------------*/
// JBlock
/*-----------------------------------------------------------------------------------------------------------------------------------*/




JBlock::JBlock(Cell ***bd, int level) {
    type='J';
    this->level=level;
    x[0] = 2;y[0] = height-5;
    x[1] = 1;y[1] = height-5;
    x[2] = 0;y[2] = height-5;
    x[3] = 0;y[3] = height-4;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}


bool JBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){               //check if it is clockwise
        tempStatus=(status + 1)%4;
        
        
        if (tempStatus == 1 ) {        // rotate from 0 to 1
            tempX[0] = x[0]-2; tempY[0] = y[0];
            tempX[1] = x[1]-1; tempY[1] = y[1]+1;
            tempX[2] = x[2]; tempY[2] = y[2]+2;
            tempX[3] = x[3]+1; tempY[3] = y[3]+1;
        }
        
        else if (tempStatus == 2) {   //rotate from 1 to 2
            tempX[0] = x[0]; tempY[0] = y[0]+1;
            tempX[1] = x[1]+1; tempY[1] = y[1];
            tempX[2] = x[2]+2; tempY[2] = y[2]-1;
            tempX[3] = x[3]+1; tempY[3] = y[3]-2;
            
        }
        else if (tempStatus == 3) {  //rotate from 2 to 3
            tempX[0] = x[0]+1; tempY[0] = y[0]+1;
            tempX[1] = x[1]; tempY[1] = y[1];
            tempX[2] = x[2]-1; tempY[2] = y[2]-1;
            tempX[3] = x[3]-2; tempY[3] = y[3];
        }
        else {                       //tempstatus=0, rotate from 3 to 0
            tempX[0] = x[0]+1; tempY[0] = y[0]-2;
            tempX[1] = x[1]; tempY[1] = y[1]-1;
            tempX[2] = x[2]-1; tempY[2] = y[2];
            tempX[3] = x[3]; tempY[3] = y[3]+1;
        }
    }
    else if(type=='C'){           //check if it is counterclock
        tempStatus=(status +3)%4;
        
        if (tempStatus == 1) {     //rotate from 2 to 1
            tempX[0] = x[0]; tempY[0] = y[0]-1;
            tempX[1] = x[1]-1; tempY[1] = y[1];
            tempX[2] = x[2]-2; tempY[2] = y[2]+1;
            tempX[3] = x[3]-1; tempY[3] = y[3]+2;
        }
        else if(tempStatus == 2) {   //rotate form 3 to 2
            tempX[0] = x[0]-1; tempY[0] = y[0]-1;
            tempX[1] = x[1]; tempY[1] = y[1];
            tempX[2] = x[2]+1; tempY[2] = y[2]+1;
            tempX[3] = x[3]+2; tempY[3] = y[3];    
        }
        else if (tempStatus == 3) { //rotate from 0 to 3
            tempX[0] = x[0]-1; tempY[0] = y[0]+2;
            tempX[1] = x[1]; tempY[1] = y[1]+1;
            tempX[2] = x[2]+1; tempY[2] = y[2];
            tempX[3] = x[3]; tempY[3] = y[3]-1;
        }
        else {  //rotate from 1 to 0
            tempX[0] = x[0]+2; tempY[0] = y[0];
            tempX[1] = x[1]+1; tempY[1] = y[1]-1;
            tempX[2] = x[2]; tempY[2] = y[2]-2;
            tempX[3] = x[3]-1; tempY[3] = y[3]-1;
        }
    }
    
    
    
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}   



/*-----------------------------------------------------------------------------------------------------------------------------------*/
// LBlock
/*-----------------------------------------------------------------------------------------------------------------------------------*/



LBlock::LBlock(Cell*** bd, int level){
    type ='L';
    this->level=level;
    x[0] = 0;y[0] = height-5;
    x[1] = 1;y[1] = height-5;
    x[2] = 2;y[2] = height-5;
    x[3] = 2;y[3] = height-4;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}

bool LBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){               //check if it is clockwise
        tempStatus=(status + 1)%4;
        
        if (tempStatus == 1 ) {        // rotate from 0 to 1
            tempX[0] = x[0]; tempY[0] = y[0]+2;
            tempX[1] = x[1]-1; tempY[1] = y[1]+1;
            tempX[2] = x[2]-2; tempY[2] = y[2];
            tempX[3] = x[3]-1; tempY[3] = y[3]-1;
        }
        
        else if(tempStatus == 2) {   //1 to 2
            tempX[0] = x[0]+2; tempY[0] = y[0]-1;
            tempX[1] = x[1]+1; tempY[1] = y[1];
            tempX[2] = x[2]; tempY[2] = y[2]+1;
            tempX[3] = x[3]-1; tempY[3] = y[3];
        }
        
        else if (tempStatus == 3) {   //2 to 3
            tempX[0] = x[0]-1; tempY[0] = y[0]-1;
            tempX[1] = x[1]; tempY[1] = y[1];
            tempX[2] = x[2]+1; tempY[2] = y[2]+1;
            tempX[3] = x[3]; tempY[3] = y[3]+2;
        }
        else {    // 3 to 0
            tempX[0] = x[0]-1; tempY[0] = y[0];
            tempX[1] = x[1]; tempY[1] = y[1]-1;
            tempX[2] = x[2]+1; tempY[2] = y[2]-2;
            tempX[3] = x[3]+2; tempY[3] = y[3]-1;
        }
    }
    
    else if(type=='C'){           //check if it is counterclock
        tempStatus=(status + 3)%4;
        
        if (tempStatus == 1) {     //rotate from 2 to 1
            tempX[0] = x[0]-2; tempY[0] = y[0]+1;
            tempX[1] = x[1]-1; tempY[1] = y[1];
            tempX[2] = x[2]; tempY[2] = y[2]-1;
            tempX[3] = x[3]+1; tempY[3] = y[3];
        }
        
        else if(tempStatus == 2) {   //rotate form 3 to 2
            tempX[0] = x[0]+1; tempY[0] = y[0]+1;
            tempX[1] = x[1]; tempY[1] = y[1];
            tempX[2] = x[2]-1; tempY[2] = y[2]-1;
            tempX[3] = x[3]; tempY[3] = y[3]-2;
        }
        
        else if (tempStatus == 3) { //rotate from 0 to 3
            tempX[0] = x[0]+1; tempY[0] = y[0];
            tempX[1] = x[1]; tempY[1] = y[1]+1;
            tempX[2] = x[2]-1; tempY[2] = y[2]+2;
            tempX[3] = x[3]-2; tempY[3] = y[3]+1;
        }
        
        else {  //rotate from 1 to 0
            tempX[0] = x[0]; tempY[0] = y[0]-2;
            tempX[1] = x[1]+1; tempY[1] = y[1]-1;
            tempX[2] = x[2]+2; tempY[2] = y[2];
            tempX[3] = x[3]+1; tempY[3] = y[3]+1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
// SBlock
/*-----------------------------------------------------------------------------------------------------------------------------------*/



SBlock::SBlock(Cell*** bd, int level) {
    type ='S';
    this->level=level;
    x[0] = 0;y[0] = height-5;
    x[1] = 1;y[1] = height-5;
    x[2] = 1;y[2] = height-4;
    x[3] = 2;y[3] = height-4;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}




bool SBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){//clock
        tempStatus=(status + 1)%4;
    }
    else if(type=='C'){//counterclock
        tempStatus=(status + 3)%4;
    }
    
    if (tempStatus%2 == 0) {     // tempstatus = 0 or 2
        tempX[0] = x[0]; tempY[0] = y[0]-2;
        tempX[1] = x[1]+1; tempY[1] = y[1]-1;
        tempX[2] = x[2]; tempY[2] = y[2];
        tempX[3] = x[3]+1; tempY[3] = y[3]+1;
    } else {                   // tempstatus = 1 or 3
        tempX[0] = x[0]; tempY[0] = y[0]+2;
        tempX[1] = x[1]-1; tempY[1] = y[1]+1;
        tempX[2] = x[2]; tempY[2] = y[2];
        tempX[3] = x[3]-1; tempY[3] = y[3]-1;
    }
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
// ZBlock
/*-----------------------------------------------------------------------------------------------------------------------------------*/


ZBlock::ZBlock(Cell*** bd, int level) {
    type ='Z';
    this->level=level;
    x[0] = 0;y[0] = height-4;
    x[1] = 1;y[1] = height-4;
    x[2] = 1;y[2] = height-5;
    x[3] = 2;y[3] = height-5;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}

bool ZBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){//clock
        tempStatus=(status + 1)%4;
    }
    else if(type=='C'){//counterclock
        tempStatus=(status + 3)%4;
    }
    
    if (tempStatus%2 == 0) {     // tempstatus = 0 or 2
        tempX[0] = x[0]-1; tempY[0] = y[0]-1;
        tempX[1] = x[1]; tempY[1] = y[1];
        tempX[2] = x[2]+1; tempY[2] = y[2]-1;
        tempX[3] = x[3]+2; tempY[3] = y[3];
    } else {                   // tempstatus = 1 or 3
        tempX[0] = x[0]+1; tempY[0] = y[0]+1;
        tempX[1] = x[1]; tempY[1] = y[1];
        tempX[2] = x[2]-1; tempY[2] = y[2]+1;
        tempX[3] = x[3]-2; tempY[3] = y[3];
    }
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
// TBlock
/*-----------------------------------------------------------------------------------------------------------------------------------*/


TBlock::TBlock(Cell*** bd, int level) {
    type ='T';
    this->level=level;
    x[0] = 0;y[0] = height-4;
    x[1] = 1;y[1] = height-4;
    x[2] = 2;y[2] = height-4;
    x[3] = 1;y[3] = height-5;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}



bool TBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){               //check if it is clockwise
        tempStatus=(status + 1)%4;
        
        if (tempStatus == 1 ) {        // rotate from 0 to 1
            tempX[0] = x[0]+1; tempY[0] = y[0]+1;
            tempX[1] = x[1]; tempY[1] = y[1];
            tempX[2] = x[2]-1; tempY[2] = y[2]-1;
            tempX[3] = x[3]-1; tempY[3] = y[3]+1;
        }
        
        else if(tempStatus == 2) {   //1 to 2
            tempX[0] = x[0]+1; tempY[0] = y[0]-2;
            tempX[1] = x[1]; tempY[1] = y[1]-1;
            tempX[2] = x[2]-1; tempY[2] = y[2];
            tempX[3] = x[3]+1; tempY[3] = y[3];
        }
        
        else if (tempStatus == 3) {   //2 to 3
            tempX[0] = x[0]-2; tempY[0] = y[0];
            tempX[1] = x[1]-1; tempY[1] = y[1]+1;
            tempX[2] = x[2]; tempY[2] = y[2]+2;
            tempX[3] = x[3]; tempY[3] = y[3];
        }
        else {    // 3 to 0
            tempX[0] = x[0]; tempY[0] = y[0]+1;
            tempX[1] = x[1]+1; tempY[1] = y[1];
            tempX[2] = x[2]+2; tempY[2] = y[2]-1;
            tempX[3] = x[3]; tempY[3] = y[3]-1;
        }
    }
    
    else if(type=='C'){           //check if it is counterclock
        tempStatus=(status + 3)%4;
        
        if (tempStatus == 1) {     //rotate from 2 to 1
            tempX[0] = x[0]-1; tempY[0] = y[0]+2;
            tempX[1] = x[1]; tempY[1] = y[1]+1;
            tempX[2] = x[2]+1; tempY[2] = y[2];
            tempX[3] = x[3]-1; tempY[3] = y[3];
        }
        
        else if(tempStatus == 2) {   //rotate form 3 to 2
            tempX[0] = x[0]+2; tempY[0] = y[0];
            tempX[1] = x[1]+1; tempY[1] = y[1]-1;
            tempX[2] = x[2]; tempY[2] = y[2]-2;
            tempX[3] = x[3]; tempY[3] = y[3];
        }
        
        else if (tempStatus == 3) { //rotate from 0 to 3
            tempX[0] = x[0]; tempY[0] = y[0]-1;
            tempX[1] = x[1]-1; tempY[1] = y[1];
            tempX[2] = x[2]-2; tempY[2] = y[2]+1;
            tempX[3] = x[3]; tempY[3] = y[3]+1;
        }
        
        else {  //rotate from 1 to 0
            tempX[0] = x[0]-1; tempY[0] = y[0]-1;
            tempX[1] = x[1]; tempY[1] = y[1];
            tempX[2] = x[2]+1; tempY[2] = y[2]+1;
            tempX[3] = x[3]+1; tempY[3] = y[3]-1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
// OBlock
/*-----------------------------------------------------------------------------------------------------------------------------------*/


OBlock::OBlock(Cell*** bd, int level) {
    type ='O';
    this->level=level;
    x[0] = 0;y[0] = height-5;
    x[1] = 1;y[1] = height-5;
    x[2] = 0;y[2] = height-4;
    x[3] = 1;y[3] = height-4;
    status = 0;
    CellCount = 4;
    this->bd = bd;
    reset();
}


bool OBlock::rotate(char type) {
    int tempX[4]; int tempY[4];
    int tempStatus;
    
    if(type=='T'){//clock
        tempStatus=(status + 1)%4;
    }
    else if(type=='C'){//counterclock
        tempStatus=(status + 3)%4;
    }
    
    tempX[0] = x[0]; tempY[0] = y[0];
    tempX[1] = x[1]; tempY[1] = y[1];
    tempX[2] = x[2]; tempY[2] = y[2];
    tempX[3] = x[3]; tempY[3] = y[3];
    
    for (int i = 0; i < 4; i++) {
        if (tempX[i] >= width || tempX[i]<0 || bd[tempY[i]][tempX[i]]->currBlock != NULL) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        x[i] = tempX[i]; y[i] = tempY[i];
    }
    status=tempStatus;
    return true;
}
