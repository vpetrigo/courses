plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week05.task03.MyApplyKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("org.junit.jupiter:junit-jupiter-api:5.2.0")
}
