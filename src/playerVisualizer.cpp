//
// Created by Jalma on 28/04/2023.
//

#include "playerVisualizer.hpp"
#include "threepp/geometries/EdgesGeometry.hpp"
#include "threepp/geometries/ExtrudeGeometry.hpp"

std::shared_ptr<Mesh> Player::playerModelCreation(){
    float x = 0, y = 0;

    auto arrowShape = Shape();
    arrowShape.moveTo(x,y)
        .lineTo(x+2,y+2)
        .lineTo(x,y-1)
        .lineTo(x+3,y)
        .lineTo(x,y-2)
        .lineTo(x-3,y)
        .lineTo(x,y-1)
        .lineTo(x-2,y+2);

    auto arrowGeometry = ShapeGeometry::create(arrowShape);
    arrowGeometry->center();
    arrowGeometry->scale(1,1,1);

    auto arrowMaterial = MeshPhongMaterial::create();
    arrowMaterial->color = Color::blue;

    auto arrow = Mesh::create(arrowGeometry,arrowMaterial);

    return arrow;
}