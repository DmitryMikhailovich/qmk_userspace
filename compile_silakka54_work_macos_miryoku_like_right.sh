if ! grep MASTER_RIGHT ./keyboards/silakka54/keymaps/work_macos_miryoku_like/config.h; then
    echo '#define MASTER_RIGHT is missing, appending to config.h'
    printf '#define MASTER_RIGHT' >> ./keyboards/silakka54/keymaps/work_macos_miryoku_like/config.h
fi
qmk compile -kb silakka54 -km work_macos_miryoku_like
sed -i '/#define MASTER_RIGHT/d' ./keyboards/silakka54/keymaps/work_macos_miryoku_like/config.h
