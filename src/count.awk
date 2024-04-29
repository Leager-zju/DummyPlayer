$3 ~ /log-in/ {     # $3 表示对每一行用空格进行 split 后的第三列（awk 的列索引从 1 开始），~ 表示匹配，!~ 表示不匹配，模式用两个 / 包裹
    ids[$6] += 1    # 全局有效
} 
$3 ~ /add-item/ {
    count[$4] += $7
}
$3 ~ /sub-item/ {
    count[$4] -= $7
}
END {
    for (id in ids) {
        print "user", id, "log in", ids[id], "times"
    }
    for (item in count) {
        c = count[item]
        if (c > 0) { 
            print "item", item, "added", c, "times"
        } else if (c < 0) {
            print "item", item, "decreased", c, "times"
        }
    }
}