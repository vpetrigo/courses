plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week04.task01.PropertyKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("junit:junit:4.12")
}
