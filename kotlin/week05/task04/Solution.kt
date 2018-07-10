fun renderProductTable(): String {
    return html {
        table {
            tr(getTitleColor()) {
                td {
                    text("Product")
                }
                td {
                    text("Price")
                }
                td {
                    text("Popularity")
                }
            }
            val products = getProducts()
            
            products.forEachIndexed { index, product ->
                tr {
                    td(getCellColor(index, 0)) {
                        text(product.description)  
                    }
                    td(getCellColor(index, 1)) {
                        text(product.price)  
                    }
                    td(getCellColor(index, 2)) {
                        text(product.popularity)  
                    }
                }
            }
        }
    }.toString()
}

fun getTitleColor() = "#b9c9fe"
fun getCellColor(index: Int, row: Int) = if ((index + row) %2 == 0) "#dce4ff" else "#eff2ff"
