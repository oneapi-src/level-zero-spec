
tag=loki-ubuntu18:1
tag2=crap
ifdef DOCKER_REGISTRY
tag2=-t ${DOCKER_REGISTRY}/${tag}
endif

all:
	docker build -t $(tag) $(tag2) -f Dockerfile.ubuntu18 .

push:
	docker push $(DOCKER_REGISTRY)/$(tag)
