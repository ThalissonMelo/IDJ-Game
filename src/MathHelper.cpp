#include "MathHelper.h"
#define PI 3.141592653589793

float MathHelper::Cos(float angle){
  return cos(angle * (PI/180)); 
}
float MathHelper::Sin(float angle){
  return sin(angle * (PI/180)); 

}