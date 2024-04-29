$3 ~ /log-in/ {
    ids[$6] += 1
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
            print "item", item, "decreased", c, "times"
        } else if (c < 0) {
            print "item", item, "added", c, "times"
        }
    }
}