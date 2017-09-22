#include "ScaleValues.h"

void ScaleValues::setValue(Vector3D<float> Values, float sum, float product){
    scaled.x = (Values.x + sum) * product;
    scaled.y = (Values.y + sum) * product;
    scaled.z = (Values.z + sum) * product;
}

Vector3D<float> ScaleValues::getValues(){
    return scaled;
}
