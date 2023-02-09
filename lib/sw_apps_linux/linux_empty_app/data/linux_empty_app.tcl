proc swapp_get_name {} {
    return "Linux Empty Application";
}

proc swapp_get_description {} {
    return "A blank Linux C project.";
}

proc swapp_is_supported_hw {} {
    return 1;
}

proc swapp_is_supported_sw {} {
    return 1;
}

proc swapp_generate {} {
}

proc swapp_get_linker_constraints {} {
    return "lscript no";
}

proc swapp_get_supported_processors {} {
    return "ps7_cortexa9 psu_cortexa53 microblaze psv_cortexa72";
}

proc swapp_get_supported_os {} {
    return "linux";
}
