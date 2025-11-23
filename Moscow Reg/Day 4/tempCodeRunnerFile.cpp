auto [dir1, dir2] = dirs[g[fromi][fromj] - 1].first;
        // auto [dir11, dir22] = dirs[g[fromi][fromj] - 1].second;
        // can = !checkOk(fromi, fromj, dir1, dir2, g) and !checkOk(fromi, fromj, dir11, dir22, g);
        // if (!can) {
        //     return false;
        // }
        // can = checkCon(fromi, fromj, dir1, dir2, g) and checkCon(fromi, fromj, dir11, dir22, g);
        // if (!can) {
        //     return false;
        // }