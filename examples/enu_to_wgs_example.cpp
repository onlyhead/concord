#include <concord/concord.hpp>

#include <iostream>

int main() {
    using namespace concord;

    // Define reference origin (Paris)
    const dp::Geo ref{48.8566, 2.3522, 35.0};

    // Create an ENU point with local offsets from the origin
    // 100m east, 200m north, 5m up from the reference point
    const frame::ENU enu{100.0, 200.0, 5.0, ref};

    std::cout << "ENU coordinates: east=" << enu.east() << ", north=" << enu.north() << ", up=" << enu.up() << "\n";
    std::cout << "Origin: lat=" << enu.origin.latitude << ", lon=" << enu.origin.longitude << "\n";

    // Convert ENU to WGS - the origin is carried in the ENU struct!
    const earth::WGS wgs = frame::to_wgs(enu);
    std::cout << "WGS coordinates: lat=" << wgs.latitude << ", lon=" << wgs.longitude << ", alt=" << wgs.altitude
              << "\n";

    // Convert back to ENU to verify round-trip
    const frame::ENU back = frame::to_enu(ref, wgs);
    std::cout << "Back to ENU: east=" << back.east() << ", north=" << back.north() << ", up=" << back.up() << "\n";

    return 0;
}
