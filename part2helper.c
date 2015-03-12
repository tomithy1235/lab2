

int checkValidChar(char c)
//This checks if the char is a valid number
//This should ONLY be called if we REQUIRE only a NUMBER (like when entering a new password)
{
	int valid = 0;
        
	if(c == '1' || c == '2' || c == '3' || c == '4' ||
            c == '5' || c == '6' || c == '7' || c == '8' ||
            c == '9' || c == '0')
        {
            valid = 1;
        }

	return valid;
}


void placeNewPassword(char passDB[][4], char newPass[], int pos)
//this updates the database of passwords with a new password
{
        
	passDB[pos][0] = newPass[0];
	passDB[pos][1] = newPass[1];
	passDB[pos][2] = newPass[2];
	passDB[pos][3] = newPass[3];
}


int checkPass(char passDB[][4],char pass[])
//this checks the password database to see if a valid entered password is correct
{
    int i,j;
    int valid = 0;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(pass[j] != passDB[i][j]){
                valid = 0;
                break;
            }
            else
                valid = 1;
        }
        if(valid == 1)
            break;
    }
    return valid;
}