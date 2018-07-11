plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week06.task01.GenericsKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("org.junit.jupiter:junit-jupiter-api:5.2.0")
    testCompile("org.junit.jupiter:junit-jupiter-params:5.2.0")
	testRuntime("org.junit.jupiter:junit-jupiter-engine:5.2.0")
}

tasks.withType<Test> {
    useJUnitPlatform()
}
