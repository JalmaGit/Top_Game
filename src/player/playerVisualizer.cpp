
#include <player/playerVisualizer.hpp>
#include <threepp/geometries/EdgesGeometry.hpp>
#include <threepp/geometries/ShapeGeometry.hpp>
#include <threepp/geometries/ExtrudeGeometry.hpp>
#include <threepp/extras/core/Shape.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/math/MathUtils.hpp>

using namespace threepp;

PlayerVisualizer::PlayerVisualizer() {
    playerModel = playerModelCreation();
}

void PlayerVisualizer::setPlayerPosition(threepp::Vector3 position, const Quaternion &rotation) const {
    playerModel->position.copy(position);
    playerModel->rotation.setFromQuaternion(rotation);
}

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

    auto arrowMaterial = MeshPhongMaterial::create();
    arrowMaterial->color = Color::blue;

    auto arrow = Mesh::create(arrowGeometry, arrowMaterial);

    ExtrudeGeometry::Options opts;
    opts.depth = 2;
    auto extrudeGeometry = ExtrudeGeometry::create(arrowShape, opts);
    extrudeGeometry->rotateZ(-math::PI / 2);
    extrudeGeometry->center();

    auto extrudeMesh = Mesh::create(extrudeGeometry, arrowMaterial);

    arrow->add(extrudeMesh);

    //arrow->castShadow = true;

    return arrow;

}



