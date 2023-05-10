//
// Created by Jalma on 28/04/2023.
//

#include "player/playerVisualizer.hpp"

#include "threepp/geometries/EdgesGeometry.hpp"
#include "threepp/geometries/ShapeGeometry.hpp"
#include "threepp/geometries/ExtrudeGeometry.hpp"
#include "threepp/extras/core/Shape.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"

using namespace threepp;

std::shared_ptr<Mesh> PlayerVisualizer::playerModelCreation() {
    float x = 0, y = 0;

    auto arrowShape = Shape();
    arrowShape.moveTo(x, y)
            .lineTo(x + 2, y + 2)
            .lineTo(x + 2, y + 1)
            .lineTo(x + 5, y + 1)
            .lineTo(x + 5, y - 1)
            .lineTo(x + 2, y - 1)
            .lineTo(x + 2, y - 2)
            .lineTo(x, y);

    auto arrowGeometry = ShapeGeometry::create(arrowShape);
    arrowGeometry->rotateZ(-math::PI / 2);
    arrowGeometry->center();
    // arrowGeometry->scale(1,1,1);

    auto arrowMaterial = MeshPhongMaterial::create();
    arrowMaterial->color = Color::blue;

    auto arrow = Mesh::create(arrowGeometry, arrowMaterial);

    ExtrudeGeometry::Options opts;
    opts.depth = 2;
    auto extrudeGeometry = ExtrudeGeometry::create(arrowShape, opts);
    extrudeGeometry->rotateZ(-math::PI / 2);
    extrudeGeometry->center();
    //extrudeGeometry->scale(1,1,1);

    auto extrudeMesh = Mesh::create(extrudeGeometry, arrowMaterial);

    arrow->add(extrudeMesh);

    return arrow;

}